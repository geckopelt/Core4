#pragma once

/// @file LocationMapObject.hxx
/// @brief An object at location map.

#include "Serialization/Serializeable.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Sprites/IAppearanceManager.hxx"
#include "Sprites/Animation.hxx"
#include "Location/IsoDirection.hxx"
#include "Location/ILocationObjectMovementListener.hxx"
#include "Pathfinding/Path.hxx"

namespace Core4
{
    /// An object (A wall, a tree, a critter, everything).
    class LocationMapObject : public Serializeable
    {
    public:
        /// Ctor. Initializes everything.
        LocationMapObject();

        /// Dtor.
        virtual ~LocationMapObject();

        /// Update an object.
        /// @param dt Update interval.
        virtual void update(float dt);

        /// Set current direction.
        /// @param direction Current isometric direction.
        void setDirection(const IsoDirection direction);

        /// Get current direection.
        /// @return Current isometric direction.
        IsoDirection getDirection() const;

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
        /// @param spriteKey Sprite name.
        /// @param direction Initial direction to set.
        void setSimpleAppearance(const std::string & spriteName, const IsoDirection direction);

        /// Set object movement listener.
        /// @see ILocationObjectMovementListener.
        /// @param listener Movement listener pointer.
        void setObjectMovementListener(ILocationObjectMovementListener * listener);

        /// Walk to neighbour cell.
        /// @param direction Walk direction.
        /// @param speed Movement speed, cells per second.
        void moveTo(const IsoDirection direction, float speed);

        /// Walk the path.
        /// @param path A path to walk.
        /// @param speed Movement speed, cells per second.
        void walkPath(const Path & path, float speed);

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
        void setMapPos(const Point & pos);

        /// Get location position.
        /// @return Location position.
        const Point & getMapPos() const;

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
        bool blocksMovement() const;

        /// Whether to block other objects movement.
        /// @param block Yes/No.
        void blockMovement(bool block);

        /// @see Serializeable
        bool skipSerialization() const;

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        bool                              m_temporary;
        size_t                            m_layer;
        std::string                       m_name;
        Point                             m_mapPos;
        Vector2                           m_tileOffset;
        Vector2                           m_startVector;
        Vector2                           m_endVector;
        float                             m_moveLerp;
        size_t                            m_direction;   // IsoDirection actually
        size_t                            m_destination; // IsoDirection actually
        float                             m_speed;
        bool                              m_visible;
        Animation                         m_animation;
        ILocationObjectMovementListener * m_movementListener;
        bool                              m_blocksMovement;
        bool                              m_selectionEnabled;
        Color                             m_color;
        Path                              m_path;
        IAppearanceManager::Appearance    m_appearance;
    };
} // namespace Core4
