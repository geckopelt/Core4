#pragma once

/// @file StringUtils.hxx
/// @brief Some userful string manipulation utils.

#include <string>
#include <vector>

namespace Core4
{

/// String manipulation helpers.
struct StringUtils
{
    /// Convert integer to a string.
    /// @param i Integer.
    /// @return Integer as string.
    static const std::string intToString(int i);

    /// Convert float to a string.
    /// @param f Float.
    /// @return Float as string.
    static const std::string floatToString(float f);

    /// Convert a string to upper case.
    /// @param str String.
    /// @return Upper case string.
    static const std::string toUpper(const std::string & str);

    /// Convert a string to lower case.
    /// @param str String.
    /// @return Lower case string.
    static const std::string toLower(const std::string & str);

    /// Split a string.
    /// @param str String to split.
    /// @param separator Separator sequence to use.
    /// @param out Splitted parts.
    static void splitString(const std::string & str, const std::string & separator, std::vector<std::string> & out);
};

} // namespace Core4
