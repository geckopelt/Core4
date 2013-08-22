#pragma once

/// @file Primitive.hxx
/// @brief A vector primitive.

#include <list>
#include "Types/Color.hxx"
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