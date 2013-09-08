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
        /// @param options Font options to parse
        /// @return Font info
        static FontInfo parseFontInfo(const FontOptions & options);

        /// Parse common font info section.
        /// @param options Font options to parse
        /// @return Common font info.
        static FontCommon parseCommonInfo(const FontOptions & options);

        /// Parse font char info.
        /// @param options Font options to parse
        /// @return Font char info.
        static FontChar parseChar(const FontOptions & options);

        /// Parse font kerning info.
        /// @param options Font options to parse
        /// @param (out) left Left character.
        /// @param (out) right Right character.
        /// @param (out) kerning Kerning, in pixels.
        static void parseKerning(const FontOptions & options, wchar_t & left, wchar_t & right, float & kerning);

        /// Parse font page info.
        /// @param options Font options to parse
        /// @param pageNumber (out) page number.
        /// @param textureName (out) texture name.
        static void parsePage(const FontOptions & options, size_t & pageNumber, std::string & textureName);

        /// Parse complete font.
        /// TODO: switch to filesystem abstraction instead.
        /// @param filename Font filename.
        /// @return Font 
        static Font parseFont(const std::string & filename); 
    };
} // namespace Core4

#endif