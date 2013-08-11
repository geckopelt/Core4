/// @file CompressionUtils.hxx
/// @brief Zlib compression utilities
#pragma once

#include <vector>

namespace Core4
{
    /// Zlib compression wrapper.
    struct CompressionUtils
    {
        /// Compress the data.
        /// @param source Data to compress.
        /// @param dest Vector to fill.
        static void compress(const std::vector<char> & source, std::vector<char> & dest);

        /// Decompress the data.
        /// @param source Data to decompress.
        /// @param dest Vector to fill.
        /// @param unpackedSize Decompressed data size, in bytes.
        static void decompress(const std::vector<char> & source, std::vector<char> & dest, size_t unpackedSize);
    };
} // namespace Core4
