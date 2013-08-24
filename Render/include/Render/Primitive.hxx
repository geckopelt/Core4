#pragma once

/// @file Primitive.hxx
/// @brief A vector primitive.

#include <list>
#include "Serialization/Serializeable.hxx"
#include "Types/Color.hxx"
#include "Types/Vector2.hxx"
#include "Render/IRenderSystem.hxx"

namespace Core4
{
    /// A vector primitive.
    class Primitive
    {
    public:
        /// Primitive is actually a set of lines.
        struct Line
        {
            IRenderSystem::PrimitivePoint start;
            IRenderSystem::PrimitivePoint end;

            Line(const Vector2 & s, const Vector2 & e, const Color & color);
            Line(float x1, float y1, float x2, float y2, const Color & color); 
            Line();
        };

        /// Draw the primitive.
        void draw(IRenderSystem * renderSystem);

        /// Clear all the lines.
        void clear();

        /// Add a line.
        void addLine(const Line & line);
    private:
        std::list<Line> m_lines;
    };
} // namespace Core4