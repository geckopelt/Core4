#pragma once

/// @file IImageWriter.hxx
/// @brief Image eriter interface

#include <string>
#include <vector>

namespace Core4
{
    /// Image writer interface.
    struct IImageWriter
    {
        /// Write image to file.
        /// @param name Destination filename
        /// @param imageData Raw image data.
        /// @param width Image width, in pixels.
        /// @param height Image height, in pixels.
        virtual void writeImage(
            const std::string & name,
            const std::vector<unsigned char> & imageData,
            const size_t width,
            const size_t height) = 0;

        virtual ~IImageWriter() {}
    };
} // namespace Core4