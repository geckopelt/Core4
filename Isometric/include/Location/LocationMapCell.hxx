#pragma once

/// @file LocationMapCell.hxx
/// @brief A location map cell.

#include "Serialization/Serializeable.hxx"
#include "Sprites/ISpriteManager.hxx"

namespace Core4
{
    /// Location map cell.
    class LocationMapCell : public Serializeable
    {
    public:
        /// Ctor.
        LocationMapCell();

        /// Ctor.
        /// @param floorTile Floor tile sprite.
        /// @param blocksMovement whether this cell blocks movement
        LocationMapCell(ISpriteManager::SpriteKey floorTile, bool blocksMovement);

        /// Set floor tile sprite.
        /// @param floorTile Floor tile sprite.
        void setFloorTile(ISpriteManager::SpriteKey floorTile);

        /// Get floor tile sprite.
        /// @return Floor tile sprite.
        const ISpriteManager::SpriteKey & getSpriteKey() const;

        /// Whether to block movement through this cell.
        /// @param block Block flag.
        void blockMovement(bool block);

        /// Does it block movement?
        /// @return Yes/No.
        bool blocksMovement() const;

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        ISpriteManager::SpriteKey m_floorTile;
        bool m_blocksMovement;
    };
} // namespace Core4
