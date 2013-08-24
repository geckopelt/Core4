#include "Types/Rect.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Rect::Rect()
    {
    }

    //------------------------------------------------------------------------------
    Rect::Rect(const Vector2 & upperLeft, const Vector2 & size) :
        m_upperLeft(upperLeft), m_size(size)
    {
    }

    //------------------------------------------------------------------------------
    void Rect::setUpperLeft(const Vector2 & upperLeft)
    {
        m_upperLeft = upperLeft;
    }

    //------------------------------------------------------------------------------
    const Vector2 & Rect::getUpperLeft() const
    {
        return m_upperLeft;
    }

    //------------------------------------------------------------------------------
    void Rect::setSize(const Vector2 & size)
    {
        m_size = size;
    }

    //------------------------------------------------------------------------------
    const Vector2 & Rect::getSize() const
    {
        return m_size;
    }

    //------------------------------------------------------------------------------
    bool Rect::pointInside(const Vector2 & pt) const
    {
        float x = m_upperLeft.x();
        float y = m_upperLeft.y();

        return 
            pt.x() >= x &&
            pt.y() >= x &&
            pt.x() < x + m_size.x() &&
            pt.y() < y + m_size.y();
    }

    //------------------------------------------------------------------------------
    void Rect::normalizePoint(Vector2 & pt) const
    {
        float x = pt.x();
        float y = pt.y();

        float rectX = m_upperLeft.x();
        float rectY = m_upperLeft.y();
        float rectWidth  = m_size.x();
        float rectHeight = m_size.y();

        if (x < rectX)
            x = rectX;
        else
        if (x >= rectX + rectWidth)
            x = rectX + rectWidth - 1;

        if (y < rectY)
            y = rectY;
        else
        if (y >= rectY + rectHeight)
            y = rectY + rectHeight - 1;

        pt = Vector2(x, y);
    }

    //------------------------------------------------------------------------------
    Rect & Rect::operator += (const Vector2 & vec)
    {
        float x = m_upperLeft.x() + vec.x();
        float y = m_upperLeft.y() + vec.y();
        m_upperLeft.setX(x);
        m_upperLeft.setY(y);
        return *this;
    }
} // namespace Core4