#pragma once

/// @file PointBase.hxx
/// @brief 2D point template

#include "Serialization/SerializeActionType.hxx"
#include "Serialization/Serializeable.hxx"

namespace Core4
{
    /// 2D point template
    template <typename T> class PointBase : public Serializeable
    {
        T m_x;
        T m_y;
    public:
        /// Default ctor. Initializes coords to zero.
        PointBase() : m_x(0), m_y(0) {}

        /// Ctor.
        PointBase(T x, T y) : m_x(x), m_y(y) {}

        /// Get x coord.
        T x() const { return m_x; }

        /// Get y coord.
        T y() const { return m_y; }

        /// Set x coord.
        void setX(T x) { m_x = x; }

        /// Set y coord.
        void setY(T y) { m_y = y; }

        bool operator < (const PointBase & other) const
        {
            return m_x < other.m_x ? true : m_y < other.m_y;
        }

        bool operator < (PointBase & other)
        {
	        return (*this) < other;
        }

        bool operator == (const PointBase & other) const
        {
	        return (other.m_x == m_x && other.m_y == m_y);
        }

        bool operator == (PointBase & other)
        {
	        return (*this == other);
        }

        /// @see Serializable
        void perform(TiXmlElement & element, const SerializeActionType action)
        {
            C4_SERIALIZE_ATTR(m_x);
            C4_SERIALIZE_ATTR(m_y);
        }
    };
};
