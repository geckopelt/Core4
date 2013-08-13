#include "Image/FakeImageLoader.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    FakeImageLoader::FakeImageLoader(const Color & color) : m_color(color) 
    {
    } 

    //------------------------------------------------------------------------------
    const std::vector<unsigned char> FakeImageLoader::loadTexture(
            const std::string & name,
            size_t & width,
            size_t & height)
    {
        const size_t BytesPerPixel = 4;
        const size_t AlphaIndex    = 3;
        const size_t RedIndex      = 2;
        const size_t GreenIndex    = 1;
        const size_t BlueIndex     = 0;
        std::vector<unsigned char> colorValue(BytesPerPixel);
        colorValue[AlphaIndex] = m_color.alpha();
        colorValue[RedIndex]   = m_color.red();
        colorValue[GreenIndex] = m_color.green();
        colorValue[BlueIndex]  = m_color.blue();

        width = 64;
        height = 32;

        std::vector<unsigned char> textureData(width * height * BytesPerPixel);
        for (size_t i = 0; i < width * height; i++)
        {
            memcpy(&textureData[i * BytesPerPixel], &colorValue[0], BytesPerPixel);
        }
        return textureData;
    }
} // namespace Core4

