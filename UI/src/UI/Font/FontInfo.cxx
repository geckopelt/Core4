#include "UI/Font/FontInfo.hxx"

namespace Core4
{
    //----------------------------------------------------------------------------------------------------------
    FontInfo::FontInfo() : m_size(0)
    {
    }

    //----------------------------------------------------------------------------------------------------------
    void FontInfo::setFace(const std::string & face)
    {
        m_face = face;
    }

    //----------------------------------------------------------------------------------------------------------
    const std::string & FontInfo::getFace() const
    {
        return m_face;
    }

    //----------------------------------------------------------------------------------------------------------
    void FontInfo::setSize(const size_t size)
    {
        m_size = size;
    }

    //----------------------------------------------------------------------------------------------------------
    const size_t FontInfo::getSize() const
    {
        return m_size;
    }

    //----------------------------------------------------------------------------------------------------------
    void FontInfo::setSpacing(const Vector2 & spacing)
    {
        m_spacing = spacing;
    }

    //----------------------------------------------------------------------------------------------------------
    const Vector2 & FontInfo::getSpacing() const
    {
        return m_spacing;
    }
} // namespace Core4