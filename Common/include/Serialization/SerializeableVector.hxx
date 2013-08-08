#pragma once

#include <vector>
#include "Serialization/SerializeableContainerBase.hxx"

namespace Core4
{
    /// A serializeable vector implementation.
    template <typename T> class SerializeableVector : public SerializeableContainerBase< T, std::vector<T> > {};
} // namespace Core4
