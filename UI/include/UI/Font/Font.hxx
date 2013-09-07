#ifndef CORE4_FONT_H
#define CORE4_FONT_H

/// @file Font.hxx
/// @brief Font class

#include <map>
#include "UI/Font/FontInfo.hxx"
#include "UI/Font/FontCommon.hxx"
#include "UI/Font/FontPages.hxx"
#include "UI/Font/FontChar.hxx"
#include "UI/Font/FontKerningInfo.hxx"

namespace Core4
{
    /// Bitmap font class.
    class Font
    {
    private:
        typedef std::map<wchar_t, FontChar> FontChars;

        FontInfo        m_info;
        FontCommon      m_common;
        FontPages       m_pages;
        FontChars       m_chars;
        FontKerningInfo m_kerning;
    };
} // namespace Core4

#endif // CORE4_FONT_H