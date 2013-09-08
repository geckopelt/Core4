#include <fstream>
#include "Utils/Guards.hxx"
#include "Image/TargaLoader.hxx"
#include "Image/TargaHeader.hxx"
#include "Image/TargaHeaderValues.hxx"

namespace Core4
{
    namespace
    {
        //----------------------------------------------------------------------------------------------------------
        bool validateHeader(const TargaHeader & header)
        {
            return 
                header.colorMapType == TargaHeaderValues::ColorMapType &&
                header.imageType == TargaHeaderValues::ImageType &&
                header.imagePixelSize == TargaHeaderValues::ImagePixelSize;
        }
    }

    //------------------------------------------------------------------------------
    const std::vector<unsigned char> TargaLoader::loadImage(
            const std::string & name,
            size_t & width,
            size_t & height)
    {
        std::ifstream stream(name, std::ios_base::binary);
        CORE4_CHECK(stream.is_open(), "Can't open file \"" + name + "\"");

        // TODO: more error handling!
        // TODO: sometimes TGA seems to be not upside-down!

        TargaHeader header;
        stream.read((char*)&header, sizeof(TargaHeader));
        CORE4_CHECK(validateHeader(header), "Unsupported Targa format");

        if (header.idFieldSize > 0)
        {
	        std::vector<char> imageIdentificationField(header.idFieldSize);
            stream.read(&imageIdentificationField[0], imageIdentificationField.size()); 
        }

	    const size_t numPixels  = header.imageWidth * header.imageHeight;
	    const size_t pixelBytes = header.imagePixelSize / 8;

        std::vector<unsigned char> bitmap(pixelBytes * numPixels);
        std::vector<unsigned char> line(header.imageWidth * pixelBytes);
        for (size_t y = 0; y < header.imageHeight; y++)
        {
            stream.read((char*)&line[0], line.size());
            memcpy(&bitmap[(header.imageHeight - y - 1) * header.imageWidth * pixelBytes], &line[0], line.size());
        }
        width  = static_cast<size_t>(header.imageWidth);
	    height = static_cast<size_t>(header.imageHeight);
        return bitmap;
    }
} // namespace Core4