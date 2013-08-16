#pragma once

/// @file IAppearanceManager.hxx
/// @brief Appearance manager interface

#include "Sprites/SpriteManager.hxx"

namespace Core4
{
    /// Appearance manager interface. Appearance is a set of sprites that defines the look of an isometric object.
    struct IAppearanceManager
    {
        typedef std::vector<ISpriteManager::SpriteKey> Appearance;

        /// Get appearance by name.
        /// @param name Appearance name.
        /// @return Appearance. Sprites in order of IsoDirection.
        /// @see IsoDirection.
        const Appearance & getAppearance(const std::string & name) const;

        /// Check appearance existense,
        /// @param name Appearance name.
        /// @return Yes/No.
        bool appearanceExists(const std::string & name) const;

        /// Add an appearance.
        /// @param name Appearance name.
        /// @param appearance Appearance. Sprites in order of IsoDirection.
        /// @see IsoDirection.
        void addAppearance(const std::string & name, const Appearance & appearance);

        /// Clear everything.
        void clear();

        virtual ~IAppearanceManager() {}
    };
} // namespace Core4
