#pragma once

/// @file LocationMapObject.hxx
/// @brief An object at location map.

#include "Serialization/Serializeable.hxx"
#include "Sprites/Animation.hxx"
#include "Location/IsoDirection.hxx"
#include "Location/ILocationObjectMovementListener.hxx"
#include "Pathfinding/Path.hxx"
#include "Sprites/ISpriteMananger.hxx"

namespace Core4
{
    /// An object (A wall, a tree, a critter, everything).
    class Object : public Serializeable
    {
    public:
        /// Ctor. Initializes everything.
        Object();

        /// Dtor.
        virtual ~Object();

        /// Update an object.
        /// @param dt Update interval.
        virtual void update(float dt);

        /// Set current direction.
        /// @param direction Current isometric direction.
        void setDirection(const IsoDirection direction);

        /// Get current direection.
        /// @return Current isometric direction.
        IsoDirection getDirection() const;

        /// Get map position.
        /// @return Map position.
        const Point &   getWorldPos() const;

        /// Get current tile offset, in pixels.
        /// @return Current tile offset, in pixels.
        const Vector2 getTileOffset() const;

        /// Get animation object.
        /// @return Animation object reference.
        Animation & getAnimation();
        
        /// Set isometric visual appearance.
        /// @param name Appearance name. Appearance is a set of sprite for all isometric directions.
        /// @param direction Initial direction to set.
        void setAppearance(const std::string & name, const IsoDirection direction);
        
        /// Set simple visual appearance (just a single sprite for all directions).
        /// @param spriteName Sprite name.
        /// @param direction Initial direction to set.
        void setSimpleAppearance(const std::string & spriteName, const int direction);

        /// Walk to neighbour cell.
        /// @param direction Walk direction.
        /// @param speed Movement speed, cells per second.
        /// @param listener Object movement callback listener.
        void moveTo(const int direction, float speed, ILocationObjectMovementListener * listener);

        /// Walk the path.
        /// @param path A path to walk.
        /// @param speed Movement speed, cells per second.
        /// @param listener Object movement callback listener.
        void walkPath(const Path & path, float speed, ILocationObjectMovementListener * listener);

        /// Is it visible?
        /// @return true if visible.
        const bool isVisible() const;

        /// Set object visibility.
        /// @param visible Visibility flag.
        void setVisible(bool visible);

        /// Set object display layer.
        /// Objects are sorted in layers.
        /// @param layer Layer number to set.
        void setLayer(size_t layer);

        /// @return Object display layer
        const size_t & getLayer() const;

        /// Set location position.
        /// @param pos Cell to place object in.
        void setLocationPos(const Point & pos);

        /// Get location position.
        /// @return Location position.
        const Point & getLocationPos() const;

        /// Set object unique name.
        /// @param name Object name
        void setName(const std::string & name);

        /// Get object unique name.
        /// @return Object unique name
        const std::string getName() const;

        /// Is it selectable?
        /// @param enabled Selection enable flag.
        void setSelectionEnabled(bool enabled);
        
        /// Is selection enabled?
        /// @return true if enabled.
        bool selectionEnabled() const;

        /// Set object color. Useful for some effects.
        /// @param color Object color.
        void setColor(const Color & color);

        /// Get object color.
        /// @return Object color.
        const Color & getColor() const;

        /// Get all the sprite keys currently used by this object
        const std::vector<ISpriteManager::SpriteKey> & getSprites() const; 

        /// Set temporary object flag. Temporary objects are skipped on serialization.
        /// Useful for special effects and so on.
        /// @param temp Temporary flag.
        void setTemporary(bool temp);
        
        /// Is this object temporary? 
        bool isTemporary() const;

        /// Does it block movement?
        /// @return Yes/No.
        bool blockMovement(bool block);

        /// @see Serializeable
        bool skipSerialization() const;

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        bool                              m_temporary;
        size_t                            m_layer;
        std::string                       m_name;
        Point                             m_locationPos;
        Vector2                           m_tileOffset;
        Vector2                           m_startVector;
        Vector2                           m_endVector;
        float                             m_moveLerp;
        IsoDirection                      m_direction;
        int                               m_destination;
        float                             m_speed;
        bool                              m_visible;
        std::vector<size_t>               m_spriteIndices;
        Animation                         m_animation;
        ILocationObjectMovementListener * m_movementListener;
        bool                              m_blocksMovement;
        bool                              m_selectionEnabled;
        Color                             m_color;
        Path                              m_path;
    };
} // namespace C4
