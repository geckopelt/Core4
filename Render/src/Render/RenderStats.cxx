#include "Render/RenderStats.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    RenderStats::RenderStats() : m_numSprites(0), m_numTextures(0), m_fps(0), m_texturesMemory(0)
    {
    }

    //------------------------------------------------------------------------------
    void RenderStats::setNumSprites(const size_t numSprites)
    {
        m_numSprites = numSprites;
    }

    //------------------------------------------------------------------------------
    size_t RenderStats::getNumSprites() const
    {
        return m_numSprites;
    }

    //------------------------------------------------------------------------------
    void RenderStats::setNumTextures(const size_t numTextures)
    {
        m_numTextures = numTextures;
    }

    //------------------------------------------------------------------------------
    size_t RenderStats::getNumTextures() const
    {
        return m_numTextures;
    }

    //------------------------------------------------------------------------------
    void RenderStats::setFPS(size_t fps)
    {
        m_fps = fps;
    }

    //------------------------------------------------------------------------------
    size_t RenderStats::getFPS() const
    {
        return m_fps;
    }

    //------------------------------------------------------------------------------
    void RenderStats::setTexturesMemory(size_t texturesMemory)
    {
        m_texturesMemory = texturesMemory;
    }

    //------------------------------------------------------------------------------
    size_t RenderStats::getTexturesMemory() const
    {
        return m_texturesMemory;
    }
} // namespace Core4
