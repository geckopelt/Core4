#pragma once

/// @file SpriteDescriptionsLoader.hxx
/// @brief Sprite descriptions loader

#include <string>
#include "Sprites/ISpriteManager.hxx"

namespace Core4
{
    /// Sprite descriptions loader.
    struct SpriteDescriptionsLoader
    {
        /// Load sprite descriptions.
        /// @param filename Sprite descriptions file name.
        /// @param spriteManager Sprite manager to use.
        static void load(const std::string & filename, ISpriteManager * spriteManager);
    };
} // namespace Core4
