#include "Image/ImageManipulator.hxx"

namespace Core4
{
    namespace
    {
        const int BytesPerPixel = 4;
        const int RedIndex = 2;
        const int GreenIndex = 1;
        const int BlueIndex = 0;
        const int AlphaIndex = 3;
    }

    //----------------------------------------------------------------------------------------------------------
    ImageManipulator::ImageManipulator(const std::vector<unsigned char> imageData, size_t width, size_t height) :
        m_imageData(imageData.begin(), imageData.end()), m_width(width), m_height(height)
    {
    }

    //----------------------------------------------------------------------------------------------------------
    ImageManipulator::ImageManipulator(size_t width, size_t height) :
        m_imageData(width * height * BytesPerPixel), m_width(width), m_height(height)
    {
    }

    //----------------------------------------------------------------------------------------------------------
    const Color ImageManipulator::getPixel(size_t x, size_t y) const
    {
        return dwordToColor(*(unsigned long*)&m_imageData[getPixelOffset(x, y)]);
    }

    //----------------------------------------------------------------------------------------------------------
    void ImageManipulator::setPixel(size_t x, size_t y, const Color & color)
    {
        unsigned long pixel = colorToDword(color); 
        memcpy(&m_imageData[getPixelOffset(x, y)], (void*)&pixel, BytesPerPixel);
    }

    //----------------------------------------------------------------------------------------------------------
    const std::vector<unsigned char> & ImageManipulator::getRawData() const
    {
        return m_imageData;
    }

    //----------------------------------------------------------------------------------------------------------
    const size_t ImageManipulator::getWidth() const
    {
        return m_width;
    }

    //----------------------------------------------------------------------------------------------------------
    const size_t ImageManipulator::getHeight() const
    {
        return m_height;
    }

    //----------------------------------------------------------------------------------------------------------
    unsigned long ImageManipulator::colorToDword(const Color & color) const
    {
        unsigned long result(0);

        unsigned char * parts = (unsigned char*)&(result);
        parts[RedIndex]   = color.red();
        parts[GreenIndex] = color.green();
        parts[BlueIndex]  = color.blue();
        parts[AlphaIndex] = color.alpha();
        return result;
    }

    //----------------------------------------------------------------------------------------------------------
    const Color ImageManipulator::dwordToColor(unsigned long color) const
    {
        unsigned char * parts = (unsigned char *)&color;
        return Color(parts[RedIndex], parts[GreenIndex], parts[BlueIndex], parts[AlphaIndex]);
    }

    //----------------------------------------------------------------------------------------------------------
    const size_t ImageManipulator::getPixelOffset(size_t x, size_t y) const
    {
        return (y * m_width + x) * BytesPerPixel;
    }

} // namespace Core4
