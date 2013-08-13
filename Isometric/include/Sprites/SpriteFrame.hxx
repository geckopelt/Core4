#pragma once

/// @file SpriteFrame.hxx
/// @brief A single sprite frame structure.

#include "Render/IRenderSystem.hxx"

namespace Core4
{
    // A structure which describes a single sprite frame.
    struct SpriteFrame
    {
        float           textureX;    //< Upper left corner X texture coordinate, in pixels.
        float           textureY;    //< Upper left corner Y texture coordinate, in pixels.
        float           width;       //< Sprite width, in pixels.
        float           height;      //< Sprite height, in pixeld..
        bool            alpha;       //< Whether to use the alpha channel.

        /// Default ctor, initializes everything.
        SpriteFrame();

        /// Convert to Render System sprite.
        /// @return Render system sprite structure.
        IRenderSystem::Sprite toRS() const;
    };
} // namespace Core4