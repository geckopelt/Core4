#pragma once

/// @file Serializer.hxx
/// @brief XML serializer.

#include "Serialization/Serializeable.hxx"

namespace Core4
{
    /// XML Serializer.
    struct Serializer
    {
        /// Serialize object to XML.
        /// @param src Object to serialize.
        /// @param nodeName XML node name (whatever you like).
        /// @return XML string.
        static std::string serialize(Serializeable * src, const std::string & nodeName);

        /// Deserialize object from XML.
        /// @param xml Xml string to deserialize from.
        /// @param nodeName Node name to deserialize from
        /// @param dest A pointer to an object to fill.
        /// @note This method does not allocate an object. You have to pass a valid pointer to existing object.
        static void deserialize(const std::string & xml, const std::string & nodeName, Serializeable * dest);
    };
} // namespace Core4
