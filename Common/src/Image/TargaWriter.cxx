#include <fstream>
#include "Image/TargaWriter.hxx"
#include "Image/TargaHeader.hxx"
#include "Image/TargaHeaderValues.hxx"

namespace Core4
{
    //----------------------------------------------------------------------------------------------------------
    void TargaWriter::writeImage(
            const std::string & name,
            const std::vector<unsigned char> & imageData,
            const size_t width,
            const size_t height)
    {
        std::ofstream stream(name, std::ios_base::binary);
        TargaHeader header;
        memset(&header, 0, sizeof(TargaHeader));
        header.imageType = TargaHeaderValues::ImageType;
        header.colorMapType = TargaHeaderValues::ColorMapType;
        header.imagePixelSize = TargaHeaderValues::ImagePixelSize;
        header.imageDescriptorByte = TargaHeaderValues::ImageDescriptorByte;
        header.imageWidth = width;
        header.imageHeight = height;

        stream.write((char*)&header, sizeof(TargaHeader));
        const size_t pixelBytes = header.imagePixelSize / 8;
        const size_t lineWidth = header.imageWidth * pixelBytes;

        for (size_t y = 0; y < header.imageHeight; y++)
        {
            stream.write((char*)&imageData[(header.imageHeight - y - 1) * header.imageWidth * pixelBytes], lineWidth);
        }
    }

} // namespace Core4
 