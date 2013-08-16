#pragma once

/// @file TargaWriter.hxx
/// @brief Targa (TGA) image writer.

#include "Image/IImageWriter.hxx"

namespace Core4
{
    /// @param Targa (TGA) image writer.
    struct TargaWriter : IImageWriter
    {
        /// @see IImageWriter
        void writeImage(
            const std::string & name,
            const std::vector<unsigned char> & imageData,
            const size_t width,
            const size_t height);
    };
} // namespace Core4
