#pragma once

/// @file IImageLoader.hxx
/// @brief Image loader interface

#include <string>
#include <vector>

namespace Core4
{
    /// Image loader interface.
    struct IImageLoader
    {
        /// Load image as A8R8G8B8 (e.g. 32bpp) array.
	    /// @name Filename or another data source name.
	    /// @param width Output parameter to store texture width into.
        /// @param width Output parameter to store texture height into.
	    /// @return Loaded image array.
	    virtual const std::vector<unsigned char> loadTexture(
            const std::string & name,
            size_t & width,
            size_t & height) = 0;
    };

} // namespace Core4