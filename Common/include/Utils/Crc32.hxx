#pragma once

/// @file Crc32.hxx
/// @brief CRC32 calculation utility.
#include <string>

namespace Core4
{
    /// CRC32 calculation utility.
    struct Crc32
    {
        /// Calculate CRC32 checksum for a string.
        /// @param str Input string.
        /// @return CRC32 checksum
        static unsigned int calculate(const std::string & str);
    };
}
