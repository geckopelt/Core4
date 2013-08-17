#include <TinyXML.h>
#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Serialization/TypeConverters.hxx"
#include "Logging/LogHelpers.hxx"
#include "Sprites/SpriteDescriptionsLoader.hxx"

namespace Core4
{
    namespace
    {        
        //------------------------------------------------------------------------------------------------------------
        template <typename T> T getAttribute(TiXmlElement * element, const std::string & name, T defaultValue)
        {
            const char * value = element->Attribute(name.c_str());

            if (NULL == value)
            {
                std::string defaultValueStr;
                TypeConverters::toString(defaultValue, defaultValueStr);
                CORE4_LOG_WARNING("Can't find sprite attribute \"" + name + "\", defaulting to \"" + defaultValueStr + "\"");
                return defaultValue;
            }
            T result;
            TypeConverters::fromString(value, result);
            return result;
        }

        //------------------------------------------------------------------------------------------------------------
        void parseSpriteFrame(TiXmlElement * element, SpriteFrame & frame)
        {
            frame.alpha    = getAttribute<bool>(element, "alpha", true);
            frame.textureX = getAttribute<float>(element, "x", 0);
            frame.textureY = getAttribute<float>(element, "y", 0);
            frame.width    = getAttribute<float>(element, "width", 64.0f);
            frame.height   = getAttribute<float>(element, "height", 32.0f);
        }

        //------------------------------------------------------------------------------------------------------------
        void parseCommonSpriteParameters(TiXmlElement * element, ISpriteManager::SpriteItem & spriteItem, const std::string & categoryName)
        {
            spriteItem.name = categoryName + "." + getAttribute<std::string>(element, "name", "default");

            Sprite & sprite = spriteItem.sprite;

            // Sprite without a texture has no sense
            const char * textureName = element->Attribute("texture");
            CORE4_CHECK(NULL != textureName, "Sprite must have a texture!");
            sprite.setTextureName(textureName);
            
            // TODO: do we really need it here?
            sprite.setAlphaEnabled(getAttribute<bool>(element, "alpha", true));
        }

        //------------------------------------------------------------------------------------------------------------
        void parseCategory(TiXmlElement * category, const std::string & categoryName, ISpriteManager * spriteManager)
        {
            // TODO: this is really ugly. Refactor!
            const char * SpriteTagName = "simple";
            for (TiXmlElement * sprite = category->FirstChildElement(SpriteTagName);
                sprite;
                sprite = sprite->NextSiblingElement(SpriteTagName))
            {
                ISpriteManager::SpriteItem item;
                parseCommonSpriteParameters(sprite, item, categoryName);

                SpriteFrame frame;
                parseSpriteFrame(sprite, frame);
                item.sprite.addFrame(frame);

                spriteManager->addSprite(item, categoryName);
            }

            const char * AnimatedTagName = "animated";
            for (TiXmlElement * animated = category->FirstChildElement(AnimatedTagName);
                animated;
                animated = animated->NextSiblingElement(AnimatedTagName))
            {
                ISpriteManager::SpriteItem item;
                parseCommonSpriteParameters(animated, item, categoryName);

                size_t numFrames = getAttribute(animated, "numFrames", 1);

                SpriteFrame frame;
                parseSpriteFrame(animated, frame);
                item.sprite.addFrame(frame);

                float stepX = (float)getAttribute(animated, "stepX", 0);
                float stepY = (float)getAttribute(animated, "stepY", 0);
                for (size_t i = 1; i < numFrames; i++)
                {
                    frame.textureX += stepX;
                    frame.textureY += stepY;
                    item.sprite.addFrame(frame);
                }

                item.sprite.setFPS(getAttribute<size_t>(animated, "fps", 10));

                spriteManager->addSprite(item, categoryName);
            }
        }

        void handleIncludes(TiXmlElement * sprites, ISpriteManager * spriteManager)
        {
            const char * IncludeTagName = "include";
            for (TiXmlElement * include = sprites->FirstChildElement(IncludeTagName);
                include;
                include = include->NextSiblingElement(IncludeTagName))
            {
                const char * name = include->Attribute("name");
                if (NULL == name)
                {
                    CORE4_LOG_WARNING("Include: no filename specified");
                    continue;
                }
                // TODO: handle circular references
                SpriteDescriptionsLoader::load(name, spriteManager);
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------
    void SpriteDescriptionsLoader::load(const std::string & filename, ISpriteManager * spriteManager)
    {
        CORE4_LOG_SECTION("Loading sprites from \"" + filename + "\"");

        TiXmlDocument xml;
        CORE4_CHECK(xml.LoadFile(filename.c_str()), "Couldn't load \"" + filename + "\", reason: " + xml.ErrorDesc());
        TiXmlElement * sprites = xml.FirstChildElement("sprites");
        CORE4_CHECK(NULL != sprites, "\"" + filename + "\": not a sprite list");

        handleIncludes(sprites, spriteManager);

        const char * CategoryTagName = "category";
        for (TiXmlElement * category = sprites->FirstChildElement(CategoryTagName);
            category;
            category = category->NextSiblingElement(CategoryTagName))
        {
            const char * categoryName = category->Attribute("name");
            CORE4_CHECK(NULL != categoryName, "Sprite category has no name");
            parseCategory(category, categoryName, spriteManager);
        }

        CORE4_LOG_MESSAGE(StringUtils::intToString(spriteManager->getCategoryCount()) + " categories found");
        CORE4_LOG_MESSAGE(StringUtils::intToString(spriteManager->getNumSprites()) + " sprites loaded");
    }
}