#pragma once

/// @file BoundingBox.hxx
/// @brief Location map object bounding box

#include "Types/Rect.hxx"

namespace Core4
{
    /// Location map object bounding box (in pixel terms). Used for mouse selection features.
    class BoundingBox
    {
    public:
        /// Ctor.
        BoundingBox();

        /// Get bbox rect.
        /// @return Bbox rect.
        const Rect & getRect() const;

        /// Set bbox rect.
        /// @param rect Bbox rect.
        void setRect(const Rect & rect);

        /// Get map object index. 
        /// @see LocationMap.
        /// @return Map object index
        const size_t getMapIndex() const;

        /// Set map object index.
        /// @see LocationMap.
        /// @param index Map object index
        void setMapIndex(size_t index);
    private:
        Rect   m_rect;
        size_t m_objectIndex;
    };
} // namespace