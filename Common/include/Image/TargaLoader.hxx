#pragma once

#include "Image/IImageLoader.hxx"

/// @file TargaLoader.hxx
/// @brief Targa file loader

namespace Core4
{
    /// Targa (TGA) image file loader.
    struct TargaLoader : IImageLoader
    {
        /// @see IImageLoader
	    virtual const std::vector<unsigned char> loadImage(
            const std::string & name,
            size_t & width,
            size_t & height);
    };
} // namespace Core4