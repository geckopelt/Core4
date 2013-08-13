#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Sprites/Sprite.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Sprite::Sprite() : m_fps(0), m_alphaEnabled(false), m_texture(NULL)
    {
    }

    //------------------------------------------------------------------------------
    const SpriteFrame & Sprite::getFrame(size_t index) const
    {
        CORE4_CHECK(index < m_frames.size(), 
            "Invalid sprite index: " + 
            StringUtils::intToString(index) + 
            ", max = " + 
            StringUtils::intToString(m_frames.size()));
        return m_frames.at(index);
    }

    //------------------------------------------------------------------------------
    const size_t Sprite::getFrameCount() const
    {
        return m_frames.size();
    }

    //------------------------------------------------------------------------------
    const size_t Sprite::getFPS() const
    {
        return m_fps;
    }

    //------------------------------------------------------------------------------
    const bool Sprite::isAlphaEnabled() const
    {
        return m_alphaEnabled;
    }

    //------------------------------------------------------------------------------
    void Sprite::addFrame(const SpriteFrame & frame)
    {
        m_frames.push_back(frame);
    }

    //------------------------------------------------------------------------------
    void Sprite::setTextureName(const std::string & textureName)
    {
        m_textureName = textureName;
    }

    //------------------------------------------------------------------------------
    void Sprite::setAlphaEnabled(bool alpha)
    {
        m_alphaEnabled = alpha;
    }

    //------------------------------------------------------------------------------
    void Sprite::setFPS(const size_t fps)
    {
        m_fps = fps;
    }

    //------------------------------------------------------------------------------
    const std::string & Sprite::getTextureName() const
    {
        return m_textureName;
    }

    //------------------------------------------------------------------------------
    ITexture * Sprite::getTexture() const
    {
        return m_texture;
    }

    void Sprite::setTexture(ITexture * texture)
    {
        m_texture = texture;
    }

    bool Sprite::hasTexture() const
    {
        return (NULL != m_texture);
    }
} // namespace Core4
