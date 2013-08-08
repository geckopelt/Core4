/// @file SerializeableContainerBase.hxx
/// @brief Serializeable container base
#pragma once

#include "Utils/StringUtils.hxx"
#include "Serialization/Serializeable.hxx"
#include "Serialization/SerializationUtils.hxx"

namespace Core4
{
    /// Serializeable container base
    template <typename ValueT, typename ContainerT> class SerializeableContainerBase :
        public Serializeable,
        public ContainerT
    {
    public:
        virtual void perform(TiXmlElement & element, const SerializeActionType action)
        {
            typename ContainerT::size_type count(ContainerT::size());
            C4_SERIALIZE_ATTR(count);
            if (action == Deserialize)
            {
                ContainerT::clear();
                ContainerT::resize(count);
            }
            size_t counter(0);
            for (typename ContainerT::iterator it = ContainerT::begin(); it != ContainerT::end(); it++)
            {
                const std::string itemName = std::string("item_") + StringUtils::intToString(counter);
                C4_SERIALIZE_CHILD(*it, itemName.c_str());
                counter++;
            }
        }
    };
} // namespace Core4