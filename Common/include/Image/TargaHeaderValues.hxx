#pragma once

/// @file TargaHeaderValues.hxx
/// @brief Valid Targa header values

namespace Core4
{
    /// Targa header values.
    struct TargaHeaderValues
    {
        static const unsigned char ColorMapType = 0;        //< We don't accept colormapped targas
        static const unsigned char ImageType = 2;           //< Unmapped RGB
        static const unsigned char ImagePixelSize = 32;     //< Only 32-bit targa files are ok
        static const unsigned char ImageDescriptorByte = 8; //< ?
    };
} // namespace Core4