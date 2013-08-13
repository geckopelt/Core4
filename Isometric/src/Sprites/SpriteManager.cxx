// #include "C4XmlDocument.hxx"
// #include "C4FileSystem.hxx"
// #include "C4TextureResource.hxx"

#include "Utils/Guards.hxx"
#include "Utils/Crc32.hxx"
#include "Utils/StringUtils.hxx"
#include "Logging/LogHelpers.hxx"
#include "Sprites/SpriteManager.hxx"

namespace Core4
{
    //----------------------------------------------------------------------------------------------------
    SpriteManager::SpriteManager() : m_renderSystem(NULL)
    {
    }

    //----------------------------------------------------------------------------------------------------
    void SpriteManager::init(IRenderSystem * parentRender)
    {
        CORE4_CHECK(NULL != parentRender, "Render is NULL");
        m_renderSystem = parentRender;
    }

    //----------------------------------------------------------------------------------------------------
    void SpriteManager::addSprite(const SpriteManager::SpriteItem & item, const std::string & categoryName)
    {
        SpriteKey key = createSpriteKey(item.name);
        if (m_sprites.find(key) != m_sprites.end())
        {
            CORE4_LOG_WARNING("Warning: duplicate sprite name \"" + item.name + "\"");
        }
        m_sprites[key] = item;
        SpriteCategories::iterator it = m_catInfo.find(categoryName);
        if (it != m_catInfo.end())
        {
            it->second.spriteKeys.push_back(key);
        }
        else
        {
            SpriteCategory category;
            category.spriteKeys.push_back(key);
            m_catInfo[categoryName] = category;
        }
    }

    //----------------------------------------------------------------------------------------------------
    const Sprite & SpriteManager::getSprite(const std::string & name)
    {
        return getSprite(Crc32::calculate(name));
    }

    //----------------------------------------------------------------------------------------------------
    const Sprite & SpriteManager::getSprite(const SpriteKey & key)
    {
        Sprite & sprite = findSpriteItem(key).sprite;
        if (NULL == sprite.getTexture()) // Load texture if not loaded yet
        {
            // TODO: add a smart loader
            ITexture * texture = m_renderSystem->getTexture(sprite.getTextureName(), NULL);
            sprite.setTexture(texture);
        }
        return sprite;    
    }

    /// Get sprite name.
    /// @param key Sprite key.
    /// @return Sprite name.
    std::string SpriteManager::getSpriteName(const SpriteKey & key)
    {
        return findSpriteItem(key).name;
    }

    //----------------------------------------------------------------------------------------------------
    bool SpriteManager::spriteExists(const std::string & name)
    {
        return m_sprites.find(createSpriteKey(name)) != m_sprites.end();
    }

    //----------------------------------------------------------------------------------------------------
    const SpriteManager::Sprites & SpriteManager::getSpriteList() const
    {
        return m_sprites;
    }

    //----------------------------------------------------------------------------------------------------
    const size_t SpriteManager::getNumSprites() const
    {
        return m_sprites.size();
    }

    //----------------------------------------------------------------------------------------------------
    const SpriteManager::SpriteCategory & SpriteManager::getCategoryInfo(const std::string & name)
    {
        SpriteCategories::const_iterator it = m_catInfo.find(name);
        CORE4_CHECK(it != m_catInfo.end(), "Unknown sprite category name: \"" + name + "\"");
        return it->second;
    }

    //----------------------------------------------------------------------------------------------------
    void SpriteManager::clear()
    {
        m_catInfo.clear();
        m_sprites.clear();
    }

    //----------------------------------------------------------------------------------------------------
    size_t SpriteManager::getCategoryCount() const
    {
        return m_catInfo.size();
    }

    //----------------------------------------------------------------------------------------------------
    SpriteManager::SpriteItem & SpriteManager::findSpriteItem(const SpriteKey & key)
    {
        Sprites::iterator it = m_sprites.find(key);
        CORE4_CHECK(it != m_sprites.end(), "Sprite with key " + StringUtils::intToString(key) + " does not exist");
        return it->second;
    }

    //----------------------------------------------------------------------------------------------------
    const SpriteManager::SpriteKey SpriteManager::createSpriteKey(const std::string & spriteName) const
    {
        return Crc32::calculate(spriteName);
    }
} // namespace C4
