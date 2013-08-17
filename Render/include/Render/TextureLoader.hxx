#pragma once

/// @file TextureLoader.hxx
/// @brief A texture loader wrapper.

#include "Utils/Singleton.hxx"
#include "Image/IImageLoader.hxx"

namespace Core4
{
    /// A common texture loader facade.
    class TextureLoader : public IImageLoader, public Singleton<TextureLoader>
    {
        /// @see IImageLoader
	    const std::vector<unsigned char> loadImage(
            const std::string & name,
            size_t & width,
            size_t & height);
    };
}