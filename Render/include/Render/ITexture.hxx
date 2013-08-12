#pragma once

/// @file ITexture.hxx
/// @brief Texture interface

#include <string>
#include "Types/Color.hxx"

namespace Core4
{
    /// A texture interface.
    struct ITexture
    {
        /// Get texture name.
        /// @return Texture name.
	    virtual const std::string & getName() const = 0;

	    /// Get texture width.
	    /// @return Texture width, in pixels.
	    virtual const size_t getWidth() const = 0;

	    /// Get texture height.
	    /// @return Texture height, in pixels.
	    virtual const size_t getHeight() const = 0;

        /// Lock the texture.
	    virtual void lock() = 0;

	    /// Get texture pixel color. Texture must be locked before this call, and unlocked after that.
	    /// @param x Pixel coordinate X.
	    /// @param y Pixel coordinate Y.
	    /// @return Pixel color.
	    virtual Color getPixel(size_t x, size_t y) = 0;

	    /// Unlock the texture.
	    virtual void unlock() = 0;

        /// Get texture size, in KB.
        /// @return Texture size, in KB.
	    virtual const size_t getSizeKB() const = 0;

        /// Get inner texture implementation.
        /// @param Inner texture implementation pointer.
        virtual void * getInnerTexture() = 0;

	    virtual ~ITexture() {}
    };
} // namespace Core4
