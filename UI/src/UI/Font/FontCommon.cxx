#include "UI/Font/FontCommon.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------
    FontCommon::FontCommon() : m_lineHeight(0.f)
    {
    }

    //--------------------------------------------------------------------------------------------
    void FontCommon::setLineHeight(float lineHeight)
    {
        m_lineHeight = lineHeight;
    }

    //--------------------------------------------------------------------------------------------
    float FontCommon::getLineHeight() const
    {
        return m_lineHeight;
    }
} // namespace Core4
