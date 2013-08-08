#pragma once

/// @file Serializable.hxx
/// @brief Base class for all serializable classes

#include <TinyXML.h>
#include "Serialization/SerializeActionType.hxx"
#include "Serialization/SerializationUtils.hxx"

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
