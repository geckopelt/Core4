#include "Tiles/TileBasics.hxx"
#include "Debug/DebugRenderingUtils.hxx"

namespace Core4
{
    void DebugRenderingUtils::addTileBordersPrimitive(const Vector2 & screenPos, const Color & color, Primitive & dest)
    {
        const size_t NumLines = 4;
        struct Offsets
        {
            float x;
            float y;
        } offsets[NumLines] = 
        {
            { 0,                         TileBasics::TileHeight / 2 },
            { TileBasics::TileWidth / 2, 0 },
            { TileBasics::TileWidth - 1, TileBasics::TileHeight / 2 },
            { TileBasics::TileWidth / 2, TileBasics::TileHeight - 1 }
        };
        struct LineOffsetIndices
        {
            size_t startIndex;
            size_t endIndex;
        } lineOffsetIndices[NumLines] = 
        {
            { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } 
        };
        for (size_t i = 0; i < NumLines; i++)
        {
            Primitive::Line line;
            line.start.x = screenPos.x() + offsets[lineOffsetIndices[i].startIndex].x;
            line.start.y = screenPos.y() + offsets[lineOffsetIndices[i].startIndex].y;
            line.start.color = color;
            line.end.x = screenPos.x() + offsets[lineOffsetIndices[i].endIndex].x;
            line.end.y = screenPos.y() + offsets[lineOffsetIndices[i].endIndex].y;
            line.end.color = color;
            dest.addLine(line);
        }
    }
} // namespace Core4
