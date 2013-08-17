/// @file Serializable.hxx
/// @brief Base class for all serializable classes

// TODO: serialization macros are ugly. Moreover, due to some circular #includes (?), they are not always
// available in certain files. Would be nice to get rid of these and use some template-based implementation instead.

/// @def C4_SERIALIZE_ATTR()
/// Declare serialization stuff for a simple object
#define C4_SERIALIZE_ATTR(what) \
    if (action == Serialize) \
    { \
        std::string str; \
        TypeConverters::toString((what), str); \
        element.SetAttribute(#what, str.c_str()); \
    } \
    else \
    { \
        const char * attr = element.Attribute(#what); \
        CORE4_CHECK(NULL != attr, "Deserialization error. No such attribute: \""#what"\""); \
        TypeConverters::fromString(attr, (what)); \
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

#pragma once

#include <TinyXML.h>
#include "Utils/Guards.hxx"
#include "Serialization/TypeConverters.hxx"
#include "Serialization/SerializeActionType.hxx"

namespace Core4
{
    /// Base class for all serializable classes.
    class Serializeable
    {
    public:
        /// Perform serialization or deserialization.
        /// @param element XML element to (de)serialize from(to).
        /// @param action Action to perform.
        virtual void perform(TiXmlElement & element, const SerializeActionType action) = 0;

        /// Should object be serialized? Sometimes it's useful (e.g. temporary objects etc)
        virtual bool skipSerialization() const { return false; }

        /// Dtor.
        virtual ~Serializeable() {}
    };
} // namespace Core4
