#include "Render/Primitive.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Primitive::Line::Line(const Vector2 & s, const Vector2 & e, const Color & color)
    {
        start.x = s.x();
        start.y = s.y();
        end.x = e.x();
        end.y = e.y();
        end.color = start.color = color;
    }

    //------------------------------------------------------------------------------
    Primitive::Line::Line(float x1, float y1, float x2, float y2, const Color & color)
    {
        start.x = x1;
        start.y = y1;
        end.x = x2;
        end.y = y2;
        end.color = start.color = color;
    }

    //------------------------------------------------------------------------------
    Primitive::Line::Line()
    {
    }

    //------------------------------------------------------------------------------
    void Primitive::clear()
    {
        m_lines.clear();
    }

    //------------------------------------------------------------------------------
    void Primitive::addLine(const Line & line)
    {
        m_lines.push_back(line);
    }

    //------------------------------------------------------------------------------
    void Primitive::draw(IRenderSystem * renderSystem)
    {
        for (std::list<Line>::const_iterator it = m_lines.begin(); it != m_lines.end(); it++)
        {
            renderSystem->drawLine(it->start, it->end);
        }
    }
}