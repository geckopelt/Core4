#pragma once

/// @file LocationMap.hxx
/// @brief A location map.

#include "Serialization/Serializeable.hxx"
#include "Serialization/SerializeableVector.hxx"
#include "Common/IUpdateable.hxx"
#include "Light/Light.hxx"
#include "Location/LocationMapCell.hxx"
#include "Location/LocationMapNode.hxx"
#include "Location/LocationMapObject.hxx"

namespace Core4
{
    /// Location Map
    class LocationMap : public Serializeable, public IUpdateable
    {
    public:
        static const int LocationMapFormatVersion = 3; //< Map format version ID, for serialization purposes. 

        // TODO: document
        static const int EmptyTile          = -1;
        static const int InvalidObjectIndex = -1;

        typedef std::list<size_t> ObjectIndexList; //< A list of object indices.
        typedef unsigned long LightId; //< A simple Light ID.
        
        /// Ctor.
        LocationMap();

        /// Create an empty map.
        /// @param width Map width, in cells.
        /// @param height Map height, in cells.
        void create(size_t width, size_t height);

        /// Get cell reference.
        /// @param pos Cell position.
        /// @return Cell reference.
        LocationMapCell & getCell(const Point & pos);
        
        /// Get node reference.
        /// @param pt Node position (in node coordinates).
        /// @return Node reference.
        LocationMapNode & getNode(const Point & pt);

        /// Get map width.
        /// @return Map width.
        const size_t getWidth() const;

        /// Get map height.
        /// @return Map height.
        const size_t getHeight() const;
       
        /// Get location map node.
        /// @param cell Cell position.
        /// @param cornerIndex Node index, 0 to 3.
        /// @return Location map node reference.
        LocationMapNode & getCellNode(const Point & cell, size_t cornerIndex);

        /// Get cell corner heights.
        /// @param cell Cell position.
        /// @param heights Cell corner heights.
        void getCellHeights(const Point & cell, std::vector<float> & heights);

        // @see IUpdateable
        void update(float dt);

        /// Check object existense.
        /// @param name Object name.
        /// @return Does object exist?
        bool objectExists(const std::string & name);
        
        /// Add an object. Object name must be unique.
        /// @param object Location object.
        void addObject(const LocationMapObject & object);

        /// Find an object by name. Throws an exception if not found, so use objectExists() first.
        /// @param name Object name.
        /// @return Object reference.
        LocationMapObject & findObject(const std::string & name);
       
        /// Get object by location-wide index.
        /// @param index Location-wide object index.
        /// @return Object reference.
        LocationMapObject & getObjectByIndex(size_t index);
  
        /// Get all objects in a specific cell.
        /// @param cell Cell position.
        /// @return Loctation-wide object indices list.
        const ObjectIndexList & getObjectsAtCell(const Point & cell) const;

        /// Get total objects count.
        /// @return Objects count.
        const size_t getNumObjects() const;

        /// Remove object by location-wide index.
        /// @param index Location-wide object index.
        void removeObjectByIndex(size_t index);

        /// Add a light source.
        /// @param light Light source object.
        /// @return Light id.
        LightId addLight(const Light & light);
        
        /// Get specific light source.
        /// @param id Light id.
        /// @return id Light object reference.
        Light & getLight(LightId id);
        
        /// Remove light by id.
        /// @param id Light id.
        void removeLight(LightId id);
        
        /// Get all existing light sources.
        /// @return Light sources vector. 
        const SerializeableVector<Light> & getLights() const;

        /// Set ambient lightning color.
        /// @param ambient Ambient light color. Note: alpha value of a color sets fog density.
        void setAmbientLight(const Color & ambient);

        /// Get ambient light color.
        /// @return Ambient light color.
        const Color & getAmbientLight() const;

        /// Get node position by cell position.
        /// @param cell Map cell.
        /// @param nodeIndex node index
        /// @return Node position.
        const Point getNodePos(const Point & cell, size_t nodeIndex) const;

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        typedef std::vector<ObjectIndexList> ObjectIndexLookup; ///< A width * height lookup array containing each cell objects indices.

        size_t                                 m_width;
        size_t                                 m_height;
        ObjectIndexLookup                      m_objectIndexLookup;
        size_t                                 m_nodesWidth;
        size_t                                 m_nodesHeight;
        Color                                  m_ambientLight;
        SerializeableVector<LocationMapObject> m_objects;
        SerializeableVector<LocationMapNode>   m_nodes;
        SerializeableVector<LocationMapCell>   m_cells;
        SerializeableVector<Light>             m_lights;
        size_t                                 m_formatVersion;
    };
} // namespace C4
