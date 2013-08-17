#include "Location/LocationMapCell.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    LocationMapCell::LocationMapCell() : m_floorTile(0), m_blocksMovement(false)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    LocationMapCell::LocationMapCell(ISpriteManager::SpriteKey floorTile, bool blocksMovement) :
        m_floorTile(floorTile), m_blocksMovement(blocksMovement)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapCell::setFloorTile(ISpriteManager::SpriteKey floorTile)
    {
        m_floorTile = floorTile;
    }

    //--------------------------------------------------------------------------------------------------------
    const ISpriteManager::SpriteKey & LocationMapCell::getSpriteKey() const
    {
        return m_floorTile;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapCell::blockMovement(bool block)
    {
        m_blocksMovement = block;
    }

    //--------------------------------------------------------------------------------------------------------
    bool LocationMapCell::blocksMovement() const
    {
        return m_blocksMovement;
    }

    //--------------------------------------------------------------------------------------------------------
    void LocationMapCell::perform(TiXmlElement & element, const SerializeActionType action)
    {
            C4_SERIALIZE_ATTR(m_floorTile);
            C4_SERIALIZE_ATTR(m_blocksMovement);
    }
} // namespace Core4
