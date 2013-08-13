#include "Sprites/SpriteFrame.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    SpriteFrame::SpriteFrame() : textureX(0), textureY(0), width(0), height(0), alpha(false)
    {
    }

    //------------------------------------------------------------------------------
    IRenderSystem::Sprite SpriteFrame::toRS() const
    {
        IRenderSystem::Sprite sprite;
        sprite.bitmapX = textureX;
        sprite.bitmapY = textureY;
        sprite.width   = width;
        sprite.height  = height;
        sprite.alpha   = alpha;
        return sprite;
    }
} // namespace Core4
