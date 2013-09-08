#pragma once

#include <memory>
#include "Utils/Guards.hxx"
#include "Utils/Factory.hxx"
#include "Utils/StringUtils.hxx"
#include "Logging/LogHelpers.hxx"
#include "Render/TextureLoader.hxx"
#include "Image/TargaLoader.hxx"
#include "Configuration/Configuration.hxx"

namespace Core4
{
    namespace
    {
        struct ImageLoaderFactory : 
            public Factory<std::string, IImageLoader>,
            public Singleton<ImageLoaderFactory>
        {
            ImageLoaderFactory()
            {
                reg<TargaLoader>("tga");
            }
        };
    }

    //----------------------------------------------------------------------------------------------------
    const std::vector<unsigned char> TextureLoader::loadImage(const std::string & name, size_t & width, size_t & height)
    {
        CORE4_CHECK(!name.empty(), "Empty texture name specified");
        std::vector<std::string> parts;
        StringUtils::splitString(name, ".", parts);
        const std::string & extension = StringUtils::toLower(parts.at(parts.size() - 1));

        const std::string texturesFolder(Configuration::getSingleton().getResourcesRoot() + "/textures/");

        std::auto_ptr<IImageLoader> loader(ImageLoaderFactory::getSingleton().create(extension));
        CORE4_CHECK(NULL != loader.get(), "Don't know how to load \"" + extension + "\" images");
        CORE4_LOG_INFO("Loading texture: \"" + name + "\"");
        return loader->loadImage(texturesFolder + name, width, height);
    }
} // namespace Core4

