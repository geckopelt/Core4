#pragma once

/// @file FakeImageLoader.hxx
/// @brief Creates generated images.

#include <string>
#include <vector>
#include "Types/Color.hxx"
#include "Image/IImageLoader.hxx"

namespace Core4
{
    /// Generates test images.
    class FakeImageLoader : public IImageLoader
    {
    public:
        /// Ctor.
        /// @param color Solid color of textures to create.
        FakeImageLoader(const Color & color);

        /// @see IImageLoader
        const std::vector<unsigned char> loadTexture(
            const std::string & name,
            size_t & width,
            size_t & height);
    private:
        Color  m_color;
    };
} // namespace 

