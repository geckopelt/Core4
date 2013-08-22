#include "Location/BoundingBox.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    BoundingBox::BoundingBox() : m_objectIndex(0)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    const Rect & BoundingBox::getRect() const
    {
        return m_rect;
    }

    //------------------------------------------------------------------------------------------------------------
    void BoundingBox::setRect(const Rect & rect)
    {
        m_rect = rect;
    }

    //------------------------------------------------------------------------------------------------------------
    const size_t BoundingBox::getMapIndex() const
    {
        return m_objectIndex;
    }

    //------------------------------------------------------------------------------------------------------------
    void BoundingBox::setMapIndex(size_t index)
    {
        m_objectIndex = index;
    }
} // namespace Core4