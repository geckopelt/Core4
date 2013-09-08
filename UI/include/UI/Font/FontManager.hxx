#ifndef CORE4_FONTMANAGER_H
#define CORE4_FONTMANAGER_H

/// @file FontManager.hxx
/// @brief UI Font Manager

#include "Utils/Singleton.hxx"
#include "UI/Font/Font.hxx"

namespace Core4
{
    /// UI Font Manager.
    class FontManager : public Singleton<FontManager>
    {
    public:
        /// Add font.
        /// @param fontName Font name.
        /// @param filename Font file to parse.
        void addFont(const std::string & fontName, const std::string & filename);

        /// Get loaded font.
        /// @param fontName Font name.
        /// @return font.
        const Font & getFont(const std::string & fontName) const;
    private:
        std::map<std::string, Font> m_fonts;
    };
} // namespace Core4

#endif // CORE4_FONTMANAGER_H