#include "Utils/Guards.hxx"
#include "Logging/LogHelpers.hxx"
#include "Location/LocationMap.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    LocationMap::LocationMap() :
        m_width(0),
        m_height(0),
        m_nodesWidth(0),
        m_nodesHeight(0),
        m_formatVersion(LocationMapFormatVersion)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::create(size_t width, size_t height)
    {
        m_cells.clear();
        m_objects.clear();
        m_lights.clear();
        m_width  = width;
        m_height = height;
        m_cells.resize(m_width * m_height);
        m_nodesWidth  = m_width * 2 + 1;
        m_nodesHeight = m_height + 1;
        m_nodes.resize(m_nodesWidth * m_nodesHeight);
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapCell & LocationMap::getCell(const Point & pos)
    {
        const size_t offset = pos.y() * m_width + pos.x();
        CORE4_CHECK(offset < m_cells.size(), "Cell position out of bounds");
        return m_cells.at(offset);
    }

    //--------------------------------------------------------------------------------------------------------
    const size_t LocationMap::getWidth() const
    {
        return m_width;
    }

    //--------------------------------------------------------------------------------------------------------
    const size_t LocationMap::getHeight() const
    {
        return m_height;
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapNode & LocationMap::getNode(const Point & pt)
    {
        const size_t offset = pt.y() * m_nodesWidth + pt.x();
        CORE4_CHECK(offset < m_nodes.size(), "Node position out of bounds");
        return m_nodes.at(offset);
    }

    //--------------------------------------------------------------------------------------------------------
    const Point LocationMap::getNodePos(const Point & cell, size_t cornerIndex) const
    {
        const size_t baseX = cell.x() * 2 + (cell.y() & 1);
        static const struct
        {
            int x, y;
        } deltas[4] =
        {
            0,  0,
            -1, 1,
            +1, 1,
            0,  2
        };
        return Point(deltas[cornerIndex].x + baseX, cell.y() + deltas[cornerIndex].y);
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapNode & LocationMap::getCellNode(const Point & cell, size_t cornerIndex)
    {
        Point pos = getNodePos(cell, cornerIndex);
        return getNode(pos);
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::update(float dt)
    {
        if (0 == m_width || 0 == m_height)
            return;

        if (m_objectIndexLookup.empty())
            m_objectIndexLookup.resize(m_width * m_height);

        for (ObjectIndexLookup::iterator it = m_objectIndexLookup.begin(); it != m_objectIndexLookup.end(); it++)
            (*it).clear();

        for (std::vector<LocationMapObject>::iterator it = m_objects.begin();it != m_objects.end(); it++)
        {
            LocationMapObject & object = (*it);
            object.update(dt);
            const Point & cellPos = object.getMapPos();
            m_objectIndexLookup.at(cellPos.y() * m_width + cellPos.x()).push_back(std::distance(m_objects.begin(), it));
        }
    }

    //--------------------------------------------------------------------------------------------------------
    const LocationMap::ObjectIndexList & LocationMap::getObjectsAtCell(const Point & cell) const
    {
        return m_objectIndexLookup.at(cell.y() * m_width + cell.x());
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapObject & LocationMap::getObjectByIndex(size_t index)
    {
        CORE4_CHECK(index < m_objects.size(), "Object index out of bounds");
        return m_objects.at(index);
    }

    //--------------------------------------------------------------------------------------------------------
    bool LocationMap::objectExists(const std::string & name)
    {
        for (std::vector<LocationMapObject>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if (name == (*it).getName())
                return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapObject & LocationMap::findObject(const std::string & name)
    {
        for (std::vector<LocationMapObject>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if (name == (*it).getName())
                return (*it);
        }
        CORE4_CHECK(false, "Could not find object: \"" + name + "\"");
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::addObject(const LocationMapObject & object)
    {
        const std::string & name = object.getName(); 
        CORE4_CHECK(!name.empty(), "Object name must not be empty");
        CORE4_CHECK(!objectExists(name), "Object already exists: \"" + name + "\"");
        m_objects.push_back(object);
    }

    //--------------------------------------------------------------------------------------------------------
    const size_t LocationMap::getNumObjects() const
    {
        return m_objects.size();
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::removeObjectByIndex(size_t index)
    {
        if (index < m_objects.size())
        {
            std::vector<LocationMapObject>::iterator it = m_objects.begin();
            std::advance(it, index);
            m_objects.erase(it);
        }
        else
            CORE4_LOG_WARNING("Object index is too large");
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMap::LightId LocationMap::addLight(const Light & light)
    {
        m_lights.push_back(light);
        return m_lights.size() - 1;
    }

    //--------------------------------------------------------------------------------------------------------
    Light & LocationMap::getLight(LightId index)
    {
        if (index < m_lights.size())
            return m_lights.at(index);
        CORE4_CHECK(false, "Invalid light ID");
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::removeLight(LightId index)
    {
        if (index < m_lights.size())
        {
            std::vector<Light>::iterator it = m_lights.begin();
            std::advance(it, index);
            m_lights.erase(it);
        }
        else
            CORE4_LOG_WARNING("Invalid light ID");
    }

    //--------------------------------------------------------------------------------------------------------
    const SerializeableVector<Light> & LocationMap::getLights() const
    {
        return m_lights;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::setAmbientLight(const Color & ambient)
    {
        m_ambientLight = ambient;
    }

    //--------------------------------------------------------------------------------------------------------
    const Color & LocationMap::getAmbientLight() const
    {
        return m_ambientLight;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMap::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_formatVersion);
        if (action == Deserialize)
        {
            CORE4_CHECK(LocationMapFormatVersion == m_formatVersion, "Invalid location map version");
        }
        C4_SERIALIZE_ATTR(m_width);
        C4_SERIALIZE_ATTR(m_height);
        C4_SERIALIZE_ATTR(m_nodesWidth);
        C4_SERIALIZE_ATTR(m_nodesHeight);
        C4_SERIALIZE_ATTR(m_ambientLight);
        C4_SERIALIZE_CHILD(m_objects,  "m_objects");
        C4_SERIALIZE_CHILD(m_lights,   "m_lights");
        C4_SERIALIZE_CHILD(m_nodes,    "m_nodes");
        C4_SERIALIZE_CHILD(m_cells,    "m_cells");
    }
} // namespace C4
