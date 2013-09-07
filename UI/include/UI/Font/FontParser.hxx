#ifndef CORE4_FONTPARSER_H
#define CORE4_FONTPARSER_H

/// @file FontParser.hxx
/// @brief Font parsing stuff

#include <string>
#include <map>
#include "UI/Font/Font.hxx"

namespace Core4
{
    /// Font parser utilities.
    struct FontParser
    {
        typedef std::map<std::string, std::string> FontOptions;

        /// Parse font options line.
        /// @param str A key-value pair line.
        /// @param tagName Tag name parsed.
        /// @return Options container.
        static FontOptions parseFontOptionsLine(const std::string & str, std::string & tagName);

        /// Parse font info
        /// @param str Font info string
        static FontInfo parseFontInfo(const std::string & str);

        /// Parse common font info section.
        /// @param str Font commons string.
        /// @return Common font info.
        static FontCommon parseCommonInfo(const std::string & str);

        /// Parse font char info.
        /// @param str Font char info string.
        /// @return Font char info.
        static FontChar parseChar(const std::string & str);

        /// Parse font kerning info.
        /// @param str Font kerning info string.
        /// @param (out) left Left character.
        /// @param (out) right Right character.
        /// @param (out) kerning Kerning, in pixels.
        static void parseKerning(const std::string & str, wchar_t & left, wchar_t & right, float & kerning);

        /// Parse font page info.
        /// @param str Font page info string.
        /// @param pageNumber (out) page number.
        /// @param textureName (out) texture name.
        static void parsePage(const std::string & str, size_t & pageNumber, std::string & textureName);

        /// Parse complete font.
        /// TODO: switch to filesystem abstraction instead.
        /// @param filename Font filename.
        /// @param font (out) Parsed font.
        static void parseFont(const std::string & filename, Font & font); 
    };
} // namespace Core4

#endif