#pragma once

/// @file Rect.hxx
/// @brief A 2D rectangle.

// TODO: Once again, an include directive quickfix.
#include "Serialization/Serializeable.hxx" 
#include "Types/Vector2.hxx"

namespace Core4
{
    /// 2D rectangle class.
    class Rect
    {
    public:
        /// Ctor.
        Rect();

        /// Ctor.
        /// @param upperLeft Upper left corner.
        /// @param size Rectangle size.
        Rect(const Vector2 & upperLeft, const Vector2 & size);

        /// Set rectangle upper left corner.
        /// @param upperLeft Upper left corner.
        void setUpperLeft(const Vector2 & upperLeft);

        /// Get rectangle upper left corner.
        /// @return Upper left corner.
        const Vector2 & getUpperLeft() const;

        /// Set rectangle size.
        /// @param size Rectangle size.
        void setSize(const Vector2 & size);

        /// Get rectangle size.
        /// @return size Rectangle size.
        const Vector2 & getSize() const;

        /// Is point inside?
        /// @param pt Point
        /// @return true if yes.
        bool pointInside(const Vector2 & pt) const;

        /// Normalize point against this rect.
        /// @param pt Point to normalize
        void normalizePoint(Vector2 & pt) const;
    private:
        Vector2 m_upperLeft;
        Vector2 m_size;
    };
} // namespace Core4