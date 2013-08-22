#include "Tiles/TileBasics.hxx"
#include "Debug/DebugRenderer.hxx"
#include "Debug/DebugRenderingUtils.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    void DebugRenderer::onNewFrame()
    {
        m_tiles.clear();
        m_objects.clear();
    }

    //------------------------------------------------------------------------------------------------------------
    void DebugRenderer::onTileRendered(const Vector2 & screenPos, const LocationMapCell & cell)
    {
        Color color = cell.blocksMovement() ? Color::Red : Color::LightGray;
        DebugRenderingUtils::addTileBordersPrimitive(screenPos, color, m_tiles);
    }

    //------------------------------------------------------------------------------------------------------------
    void DebugRenderer::onObjectRendered(const BoundingBox & boundingBox, const LocationMapObject & object)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void DebugRenderer::onRender(IRenderSystem * renderSystem)
    {
        m_tiles.draw(renderSystem);
    }
} // namespace Core4
