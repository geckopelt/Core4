#include "Serialization/Serializeable.hxx" // HACK
#include "Sprites/SpriteDescriptionsLoader.hxx"
#include "Facade/EngineFacade.hxx"
#include "Sprites/SpriteManager.hxx"
#include "Location/LocationMapCell.hxx"
#include "Input/InputController.hxx"
#include "Debug/DebugRenderingUtils.hxx"
#include "Render/Primitive.hxx"
#include "Tiles/TileBasics.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    EngineFacade::EngineFacade() : m_renderSystem(NULL)
    {
        InputController::getSingleton().subscribe(this);
    }

    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::init(IRenderSystem * renderSystem)
    {
        m_renderSystem = renderSystem;

        // TMP
        SpriteManager::getSingleton().init(renderSystem);
        SpriteDescriptionsLoader::load("../../App/data/sprites/SpriteList.xml", &SpriteManager::getSingleton()); 

        m_testMap.create(64, 64);
        for (size_t i = 0; i < m_testMap.getWidth(); i++)
        for (size_t j = 0; j < m_testMap.getHeight(); j++)
        {
            LocationMapCell & cell = m_testMap.getCell(Point(i, j)); 
            cell.setFloorTile(SpriteManager::getSingleton().getSpriteKey("Tiles.DesertTile1"));
        }

        LocationMapCell & cell = m_testMap.getCell(Point(8, 6));
        cell.blockMovement(true);

        // TMP
        m_mapRenderer.init(m_renderSystem, Vector2(640.0f, 480.0f));
        m_mapRenderer.setLocationMap(&m_testMap);
    }
 
    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::updateAndRender(float dt)
    {
        if (NULL != m_renderSystem)
        {
            m_mapRenderer.clearScreen();
            m_testMap.update(dt);
            m_mapRenderer.render();

            // TMP
            Primitive mouseCursorStub;
            Primitive::Line line;
            line.start.x = m_mousePos.x();
            line.start.y = m_mousePos.y();
            line.end.x = line.start.x + 16;
            line.end.y = line.start.y + 16;
            line.start.color = line.end.color = Color::White;
            mouseCursorStub.addLine(line);
            mouseCursorStub.draw(m_renderSystem);

            Primitive cellCursor;
            Point tilePos = m_mouseMap.screenToTile(m_mousePos, m_mapRenderer);
            Vector2 screenPos = TileBasics::getTileScreenPos(tilePos);
            DebugRenderingUtils::addTileBordersPrimitive(screenPos, Color::Blue, cellCursor);
            cellCursor.draw(m_renderSystem);

            m_renderSystem->render();
        }
    }

    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::cleanup()
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::onKeyDown(const Buttons::Type & button)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::onKeyUp(const Buttons::Type & button)
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void EngineFacade::onMouseMove(const Vector2 & mousePos)
    {
        m_mousePos = mousePos;
    }
} // namespace Core4