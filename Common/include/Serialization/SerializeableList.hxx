#pragma once

#include <list>
#include "Serialization/SerializeableContainerBase.hxx"

namespace Core4
{
    /// A serializeable list implementation.
    template <typename T> class SerializeableList : public SerializeableContainerBase< T, std::list<T> > {};
} // namespace Core4
