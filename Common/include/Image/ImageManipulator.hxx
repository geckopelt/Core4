#pragma once

/// @file ImageManipulator.hxx
/// @brief Image manipulator class.

#include <vector>
#include "Types/Color.hxx"

namespace Core4
{
    /// Image manipulator. Allows raw image buffer pixel read/write access 
    class ImageManipulator
    {
    public:
        /// Ctor.
        /// @param imageData Raw data to deal with.
        /// @param width Image width.
        /// @param height Image height.
        ImageManipulator(const std::vector<unsigned char> imageData, size_t width, size_t height);

        /// Ctor.
        /// Creates an empty image.
        /// @param width Image width.
        /// @param height Image height.
        ImageManipulator(size_t width, size_t height);

        /// Get image pixel.
        /// @param x X position.
        /// @param y Y position.
        /// @return Image pixel color.
        const Color getPixel(size_t x, size_t y) const;

        /// Set image pixel.
        /// @param x X position.
        /// @param y Y position.
        /// @param color Image pixel color.
        void setPixel(size_t x, size_t y, const Color & color);

        /// Get raw image data.
        /// @return Raw image data.
        const std::vector<unsigned char> & getRawData() const;

        /// Get image width.
        /// @return Image width, in pixeld.
        const size_t getWidth() const;

        /// Get image height.
        /// @return Image height, in pixeld.
        const size_t getHeight() const;
    private:
        unsigned long colorToDword(const Color & color) const;
        const Color dwordToColor(unsigned long color) const;
        const size_t getPixelOffset(size_t x, size_t y) const;

        std::vector<unsigned char> m_imageData;
        size_t m_width;
        size_t m_height;
    };
} // namespace Core4