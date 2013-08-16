#include <math.h>
#include "Render/IRenderSystem.hxx"
#include "Render/Circle.hxx"

namespace Core4
{
    // TODO: add a LUT

    // TODO experimental
    float degToRad(size_t deg)
    {
        return deg * 3.14f * 2/ 360.f; 
    }

    //------------------------------------------------------------------------------
    Circle::Circle(float x, float y, float radius, const Color & color)
    {
        // TODO: experimental
        const size_t NumLines = 360;
        for (size_t angle = 0; angle < NumLines; angle++)
        {
            Line line;
            line.start.x = x + radius * cosf(degToRad(angle));
            line.start.y = y + radius * sinf(degToRad(angle));
            line.end.x   = x + radius * cosf(degToRad(angle + 1));
            line.end.y   = y + radius * sinf(degToRad(angle + 1));
            line.start.color = line.end.color = color;
            addLine(line);
        }
    }
} // namespace Core4
