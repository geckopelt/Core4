#include "Logging/LogHelpers.hxx"
#include "Location/LocationMapObject.hxx"
#include "Sprites/AppearanceManager.hxx"
#include "Tiles/TileBasics.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    LocationMapObject::LocationMapObject() :
        m_temporary(false),
        m_layer(0),
        m_moveLerp(0),
        m_direction(UnknownDirection),
        m_destination(UnknownDirection),
        m_speed(0),
        m_visible(false),
        m_movementListener(NULL),
        m_blocksMovement(false),
        m_selectionEnabled(false)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapObject::~LocationMapObject()
    {
    }

    //--------------------------------------------------------------------------------------------------------
    IsoDirection LocationMapObject::getDirection() const
    {
        return static_cast<IsoDirection>(m_direction);
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapObject::setMapPos(const Point & pos)
    {
        m_mapPos = pos;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapObject::update(float dt)
    {
        const float HorizontalFactor = 1000.0f;
        const float VeritcalFactor = 500.0f;

        m_animation.update(dt);
        if (UnknownDirection != m_destination)
        {
            const float deltaMoveLerp = (dt / ( (0 != m_direction %2) ? VeritcalFactor : HorizontalFactor) ) * m_speed;
            if (m_moveLerp < 1.f)
            {
                m_moveLerp += deltaMoveLerp;
            }
            else
            {
                // This trick allows our objects to be correctly displayed one against other
	            if (m_destination != SouthWest &&
	                m_destination != SouthEast &&
	                m_destination != East &&
	                m_destination != South)
			    {
                    setMapPos(TileBasics::getNeighbourCell(m_mapPos, static_cast<IsoDirection>(m_destination)));
			    }
			    m_startVector = Vector2(0.f, 0.f);
			    m_endVector   = Vector2(0.f, 0.f);
                m_destination = UnknownDirection; // Stop movement.

                if (m_path.empty())
                {
                    // OK, we're there.
                    if (NULL != m_movementListener)
                    {
                        m_movementListener->onMovementFinished(this);
                    }
                }
                else
                {
                    // Continue walking.
                    m_path.pop_back();
                    if (!m_path.empty())
                    {
                        moveTo(m_path.at(m_path.size() - 1), m_speed);
                    }
                    else
                    {
                        if (NULL != m_movementListener)
                        {
                            m_movementListener->onMovementFinished(this);
                        }
                    }
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapObject::setObjectMovementListener(ILocationObjectMovementListener * listener)
    {
        m_movementListener = listener;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapObject::moveTo(const IsoDirection direction, float speed)
    {
        if (UnknownDirection != m_destination)
            return; // Already moving. TODO: it's quite crappy to check such a thing this way.

        m_destination = direction;
        m_moveLerp    = 0.f;
        m_speed       = speed;

        m_startVector = TileBasics::getTileScreenPos(m_mapPos);
        Point dest    = TileBasics::getNeighbourCell(m_mapPos, static_cast<IsoDirection>(m_destination));
        m_endVector   = TileBasics::getTileScreenPos(dest);

        if (m_destination == SouthWest ||
            m_destination == SouthEast ||
            m_destination == East ||
            m_destination == South)
	    {
	        setMapPos(dest);
	    }
	    setDirection(direction);
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapObject::walkPath(const Path & path, float speed)
    {
        m_path.clear();
        for (Path::const_reverse_iterator it = path.rbegin(); it != path.rend(); it++)
        {
            m_path.push_back(*it);
        }
        if (!m_path.empty())
        {
            moveTo(m_path.at(m_path.size() - 1), speed);
        }
    }

    //--------------------------------------------------------------------------------------------------------
    const Vector2 LocationMapObject::getTileOffset() const
    {
        if (UnknownDirection == m_destination)
            return Vector2(0.f, 0.f);

        const float startX = m_startVector.x();
        const float startY = m_startVector.y();
        const float endX = m_endVector.x();
        const float endY = m_endVector.y();

        const float x = startX * (1.f - m_moveLerp) + endX * m_moveLerp;
        const float y = startY * (1.f - m_moveLerp) + endY * m_moveLerp;

        if (m_destination != SouthWest &&
            m_destination != SouthEast &&
            m_destination != East &&
            m_destination != South)
        {
            return Vector2(x - startX, y - startY);
        }
        else
        {
            return Vector2(x - endX, y - endY);
        }
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setDirection(const IsoDirection direction)
    {
        if (m_appearance.empty())
        {
            CORE4_LOG_WARNING("Warning: can't set direction. Object \"" + m_name + "\" has no apperance");
            return;
        }

        m_direction = direction;
        bool isPlaying = m_animation.isPlaying();
        bool isLooped  = m_animation.isLooped();
        size_t frame     = m_animation.getCurrentFrame();

        // Change current animation.
        const size_t NumDirections = 8;
        if (NumDirections == m_appearance.size())
        {
            const ISpriteManager::SpriteKey spriteKey = m_appearance.at(static_cast<size_t>(m_direction));
            m_animation.setup(spriteKey);
        }
        else
        {
            m_animation.setup(m_appearance.at(0));
        }

        if (isPlaying)
        {
            m_animation.play(isLooped);
        }
        m_animation.setCurrentFrame(frame);
    }

    //----------------------------------------------------------------------------------------------------------
    const Point & LocationMapObject::getMapPos() const
    {
        return m_mapPos;
    }

    //----------------------------------------------------------------------------------------------------------
    Animation & LocationMapObject::getAnimation()
    {
        return m_animation;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setAppearance(const std::string & name, const IsoDirection direction)
    {
        m_appearance = AppearanceManager::getSingleton().getAppearance(name);
        setDirection(direction);
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setSimpleAppearance(const std::string & spriteName, const IsoDirection direction)
    {
        m_appearance.clear();
        m_appearance.push_back(SpriteManager::getSingleton().getSpriteKey(spriteName));
        setDirection(direction);
    }

    //----------------------------------------------------------------------------------------------------------
    const bool LocationMapObject::isVisible() const
    {
        return m_visible;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setVisible(bool visible)
    {
        m_visible = visible;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setLayer(size_t layer)
    {
        m_layer = layer;
    }

    //----------------------------------------------------------------------------------------------------------
    const size_t & LocationMapObject::getLayer() const
    {
        return m_layer;
    }

    //----------------------------------------------------------------------------------------------------------
    const std::string LocationMapObject::getName() const
    {
        return m_name;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setName(const std::string & name)
    {
        m_name = name;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setSelectionEnabled(bool enabled)
    {
        m_selectionEnabled = enabled;
    }

    //----------------------------------------------------------------------------------------------------------
    bool LocationMapObject::selectionEnabled() const
    {
        return m_selectionEnabled;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setColor(const Color & color)
    {
        m_color = color;
    }

    //----------------------------------------------------------------------------------------------------------
    const Color & LocationMapObject::getColor() const
    {
        return m_color;
    }

    //----------------------------------------------------------------------------------------------------------
    bool LocationMapObject::blocksMovement() const
    {
        return m_blocksMovement;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::blockMovement(bool block)
    {
        m_blocksMovement = block;
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::setTemporary(bool temp)
    {
        m_temporary = temp;
    }

    //----------------------------------------------------------------------------------------------------------
    bool LocationMapObject::isTemporary() const
    {
        return m_temporary;
    }

    //----------------------------------------------------------------------------------------------------------
    bool LocationMapObject::skipSerialization() const
    {
        return isTemporary();
    }

    //----------------------------------------------------------------------------------------------------------
    void LocationMapObject::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_name);
        C4_SERIALIZE_CHILD(m_mapPos, "m_mapPos");
        C4_SERIALIZE_CHILD(m_tileOffset, "m_tileOffset");
        C4_SERIALIZE_CHILD(m_startVector, "m_startVector");
        C4_SERIALIZE_CHILD(m_endVector, "m_endVector");
        C4_SERIALIZE_ATTR(m_moveLerp);
        C4_SERIALIZE_ATTR(m_direction);
        C4_SERIALIZE_ATTR(m_destination);
        C4_SERIALIZE_ATTR(m_speed);
        C4_SERIALIZE_ATTR(m_visible);
        C4_SERIALIZE_ATTR(m_appearance);
        C4_SERIALIZE_ATTR(m_blocksMovement);
        C4_SERIALIZE_ATTR(m_selectionEnabled);
        C4_SERIALIZE_ATTR(m_color);
        C4_SERIALIZE_CHILD(m_path, "m_path");
        C4_SERIALIZE_CHILD(m_animation, "m_animation");
    }
} // namespace Core4

// todo
// const std::vector<ISpriteManager::SpriteKey> & getSpriteIds() const { return m_spriteIndices; }
