#pragma once

/// @file Path.hxx
/// @brief A path to walk.

#include <vector>
#include "Serialization/Serializeable.hxx"
#include "Location/IsoDirection.hxx"

namespace Core4
{
    /// A path to walk.
    class Path : public Serializeable, public std::vector<IsoDirection>
    {
    public:
        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        const std::string toString() const;
        void fromString(const std::string & str);
    };
} // namespace Core4