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
    public:
        typedef std::map<wchar_t, FontChar> FontChars;

        /// Get font info.
        const FontInfo & getInfo() const;

        /// Get font common info.
        const FontCommon & getCommon() const;

        /// Get font pages.
        const FontPages & getPages() const;

        /// Get font chars.
        const FontChars & getChars() const;

        /// Get font kerning info.
        const FontKerningInfo & getKerningInfo() const;
    protected:
        friend struct FontParser;

        FontInfo        m_info;
        FontCommon      m_common;
        FontPages       m_pages;
        FontChars       m_chars;
        FontKerningInfo m_kerning;
    };
} // namespace Core4

#endif // CORE4_FONT_H