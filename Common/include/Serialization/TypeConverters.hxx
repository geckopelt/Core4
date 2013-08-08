#pragma once

/// @file TypeConverters.hxx
/// @brief Type converters (for serialization purposes). 

#include <string>
#include <vector>
#include "Types/Vector2.hxx"
#include "Types/Point.hxx"
#include "Types/Color.hxx"

namespace Core4
{
    /// Serialization type converters.
    struct TypeConverters
    {
        /// Bool to string.
        static void toString(bool in, std::string & out);

        /// Bool from string.
        static void fromString(const std::string & in, bool & out);

        /// Int to string.
        static void toString(int in, std::string & out);

        /// Int from string.
        static void fromString(const std::string & in, int & out);

        /// Size_t to string.
        static void toString(size_t in, std::string & out);

        /// Size_t from string.
        static void fromString(const std::string & in, size_t & out);

        /// Float to string.
        static void toString(const float & in, std::string & out);

        /// Float from string.
        static void fromString(const std::string & in, float & out);

        // Std::string to string.
        static void toString(const std::string & in, std::string & out);

        /// Std::string from string.
        static void fromString(const std::string & in, std::string & out);

        /// Color to string.
        static void toString(const Color & in, std::string & out);
 
        /// Color from string.
        static void fromString(const std::string & in, Color & out);

        /// Vector2 to string.
        static void toString(const Vector2 & in, std::string & out);

        /// Vector2 from string.
        static void fromString(const std::string & in, Vector2 & out);
 
        /// Point to string.
        static void toString(const Point & in, std::string & out);

        /// Point from string.
        static void fromString(const std::string & in, Point & out);
 
        /// Std::vector<size_t> to string.
        static void toString(const std::vector<size_t> & in, std::string & out);
 
        /// Std::vector<size_t> from string.
        static void fromString(const std::string & in, std::vector<size_t> & out);
    };
} // namespace Core4
