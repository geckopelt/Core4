#pragma once

/// @file SpriteManager.hxx
/// @brief Sprite manager

#include <map>
#include <string>
#include <list>
#include "Utils/Singleton.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Sprites/Sprite.hxx"

// TODO: use resources root!

namespace Core4
{
    /// Sprite manager.
    class SpriteManager :
        public ISpriteManager,
        public Core4::Singleton<SpriteManager>
    {
    public:
        /// Ctor.
        SpriteManager();

        /// Initialize sprite manager.
        /// @param renderSystem Render system to use.
        void init(IRenderSystem * renderSystem);

        /// @see ISpriteManager
        void addSprite(const SpriteItem & item, const std::string & categoryName);

        /// @see ISpriteManager
        const Sprite & getSprite(const std::string & name);

        /// @see ISpriteManager
        const Sprite & getSprite(const SpriteKey & key);

        /// @see ISpriteManager
        std::string getSpriteName(const SpriteKey & key);

        /// @see ISpriteManager
        const SpriteKey getSpriteKey(const std::string & name) const;

        /// @see ISpriteManager
        const Sprites & getSpriteList() const;

        /// @see ISpriteManager
        bool spriteExists(const std::string & name);

        /// @see ISpriteManager        
        const size_t getNumSprites() const;

        /// @see ISpriteManager
        const SpriteCategory & getCategoryInfo(const std::string & name);

        /// @see ISpriteManager
        void clear();

        /// @see ISpriteManager
        size_t getCategoryCount() const;

        /// Set alternative image loader.
        /// @param loader Image loader.
        void setImageLoader(IImageLoader * loader);
    private:
        SpriteItem & findSpriteItem(const SpriteKey & key);
        const SpriteKey createSpriteKey(const std::string & spriteName) const;
        
        /* TODO?
        void preLoadCheck(); */

        SpriteCategories m_catInfo;
        Sprites          m_sprites;
        IRenderSystem *  m_renderSystem;
        IImageLoader *   m_loader;
    };
} // namespace C4
