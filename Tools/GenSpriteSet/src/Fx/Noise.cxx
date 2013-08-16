#include "Fx/Noise.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------
    Noise::Noise(const Color & baseColor, unsigned char noise) : m_baseColor(baseColor), m_noise(noise)
    {
    }

    //------------------------------------------------------------------------------------------
    void Noise::applyEffect(ImageManipulator & im)
    {
        for (size_t x = 0; x < im.getWidth(); x++)
        for (size_t y = 0; y < im.getHeight(); y++)
        {
            // TMP
            unsigned char noise = rand() % m_noise;
            Color color(m_baseColor);
            color.setRed(color.red() + noise);
            color.setBlue(color.blue() + noise);
            color.setGreen(color.green() + noise);
            im.setPixel(x, y, color);
        }
    }

} // namespace Core4