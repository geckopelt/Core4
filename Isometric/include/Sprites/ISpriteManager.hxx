#pragma once

/// @file ISpriteManager.hxx
/// @brief Sprite manager interface

#include <map>
#include <string>
#include <list>
#include "Utils/Singleton.hxx"
#include "Sprites/Sprite.hxx"

namespace Core4
{
    /// Sprite manager interface
    struct ISpriteManager
    {
        typedef unsigned int SpriteKey; ///< Unique sprite key identifier

        /// Sprite item.
        struct SpriteItem
        {
            std::string name;   ///< Sprite name.
            Sprite      sprite; ///< Sprite attributes.
        };

        typedef std::map<SpriteKey, SpriteItem> Sprites; ///< Sprites container.

        /// Sprite category info.
        struct SpriteCategory
        {
            std::list<SpriteKey> spriteKeys; ///< Sprites in this category
        };

        typedef std::map<std::string, SpriteCategory> SpriteCategories; ///< Category infos.

        /// Add new sprite item.
        /// @param item Sprite item description.
        /// @param categoryName Category name
        virtual void addSprite(const SpriteItem & item, const std::string & categoryName) = 0;

        /// Get sprite reference by name.
        /// @param name Sprite name.
        /// @return Sprite reference.
        virtual const Sprite & getSprite(const std::string & name) = 0;

        /// Get sprite reference by key.
        /// @param key Sprite key.
        /// @return Sprite reference.
        virtual const Sprite & getSprite(const SpriteKey & key) = 0;

        /// Get sprite name.
        /// @param key Sprite key.
        /// @return Sprite name.
        virtual std::string getSpriteName(const SpriteKey & key) = 0;

        /// Get sprite list.
        /// @return Sprite list reference.
        virtual const Sprites & getSpriteList() const = 0;

        /// Check sprite existence
        /// @param name Sprite name.
        /// @return true if exists.
        virtual bool spriteExists(const std::string & name) = 0;

        /// Get total sprite count.
        /// @return Sprite count.
        virtual const size_t getNumSprites() const = 0;

        /// Get sprite category info.
        /// @param name Category name (e.g. "Tiles")
        virtual const SpriteCategory & getCategoryInfo(const std::string & name) = 0;

        /// Clear all the sprites.
        virtual void clear() = 0;

        /// Get sprite categories count.
        /// @return Sprite categories count.
        virtual size_t getCategoryCount() const = 0;


        virtual ~ISpriteManager();
    };
} // namespace Core4