#pragma once

/// @file XmlDocument.hxx
/// @brief A TinyXML document extension class.

#include <TinyXML.h>
#include <string>

namespace Core4
{
    /// A TinyXML document extension class
    struct XmlDocument : public TiXmlDocument
    {
        /// Convert XML structure to string
        const std::string toString() const;
    };
} // Core4
