#pragma once

/// @file LocationMapNode.hxx
/// @brief A location map node.

#include "Types/Color.hxx"
#include "Serialization/Serializeable.hxx"

namespace Core4
{
    /// A location map node. Neighboring tiles share these nodes.
    class LocationMapNode : public Serializeable
    {
    public:
        /// Ctor.
        LocationMapNode();

        /// Set height of this node. This does not affect anything except visual appearance of neighboring tiles,
        /// allowing "pseudo-3d" look.
        /// @param height Height, in pixels.
        void setHeight(float height);

        /// Get height of this node.
        /// @return Heighgt, in pixels.
        float getHeight() const;

        /// Set color of this node.
        /// @param color.
        void setColor(const Color & color);

        /// Get color of this node.
        /// @return color.
        const Color & getColor() const; 

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        float m_height;
        Color m_color;
  };

} // namespace Core4