#include "Render/Primitive.hxx"

namespace Core4
{
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