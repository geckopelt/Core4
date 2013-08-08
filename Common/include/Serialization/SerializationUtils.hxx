#pragma once

/// @file SerializationUtils.hxx
/// @brief Useful serialization macros

#include "Utils/Guards.hxx"
#include "Serialization/TypeConverters.hxx"

/// @def C4_SERIALIZATION()
/// Starts a serialization/deserialization section
#define C4_SERIALIZATION void perform(TiXmlElement & element, const Core4::SerializeActionType action)

/// @def C4_SERIALIZE_ATTR()
/// Declare serialization stuff for a simple object
#define C4_SERIALIZE_ATTR(what) \
    if (action == Serialize) \
    { \
        std::string str; \
        TypeConverters::toString(what, str); \
        element.SetAttribute(#what, str.c_str()); \
    } \
    else \
    { \
        const char * attr = element.Attribute(#what); \
        CORE4_CHECK(NULL != attr, "Deserialization error. No such attribute: \""#what"\""); \
        TypeConverters::fromString(attr, what); \
    }

/// @def C4_SERIALIZE_CHILD()
/// Declare serialization stuff for a child object, which is also serializeable.
#define C4_SERIALIZE_CHILD(what, tagName) \
    { \
        TiXmlElement * child(0); \
        if (action == Serialize && !(what).skipSerialization()) \
            child = static_cast<TiXmlElement*>(element.InsertEndChild(TiXmlElement(tagName))); \
        else \
            child = element.FirstChildElement(tagName); \
        CORE4_CHECK(NULL != child, "Child element to serialize is NULL"); \
        (what).perform(*child, action); \
    }
