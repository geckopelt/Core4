#pragma once

/// @file TargaHeader.hxx
/// @brief Targa file header

namespace Core4
{
    #pragma pack(1)
    
    /// Targa (TGA) file header
    struct TargaHeader
    {
        unsigned char  idFieldSize;
        unsigned char  colorMapType;
        unsigned char  imageType;
	    unsigned short colorMapOrigin;
	    unsigned short colorMapLength;
	    unsigned char  colorMapEntrySize;
	    unsigned short originX;
	    unsigned short originY;
    	unsigned short imageWidth;
	    unsigned short imageHeight;
	    unsigned char  imagePixelSize;
        unsigned char  imageDescriptorByte;
    };
    
    #pragma pack()
}