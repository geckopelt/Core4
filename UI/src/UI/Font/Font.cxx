#include "UI/Font/Font.hxx"

namespace Core4
{
    //----------------------------------------------------------------------------------------------------------
    const FontInfo & Font::getInfo() const
    {
        return m_info;
    }

    //----------------------------------------------------------------------------------------------------------
    const FontCommon & Font::getCommon() const
    {
        return m_common;
    }

    //----------------------------------------------------------------------------------------------------------
    const FontPages & Font::getPages() const
    {
        return m_pages;
    }

    //----------------------------------------------------------------------------------------------------------
    const Font::FontChars & Font::getChars() const
    {
        return m_chars;
    }

    //----------------------------------------------------------------------------------------------------------
    const FontKerningInfo & Font::getKerningInfo() const
    {
        return m_kerning;
    }
} // namespace Core4
