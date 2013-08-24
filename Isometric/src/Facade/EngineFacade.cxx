#include "Serialization/Serializeable.hxx" // HACK
#include "Sprites/SpriteDescriptionsLoader.hxx"
#include "Facade/EngineFacade.hxx"
#include "Sprites/SpriteManager.hxx"
#include "Location/LocationMapCell.hxx"
#include "Input/InputController.hxx"
#include "Debug/DebugRenderingUtils.hxx"
#include "Render/Primitive.hxx"
#include "Tiles/TileBasics.hxx"
#include "Light/Light.hxx"

// TODO: move engine facade to another project (Engine)

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

        Point pos(8, 10);
        for (int i = 0; i < 8; i++)
        {
            Point n = TileBasics::getNeighbourCell(pos, (IsoDirection)i);
            LocationMapCell & cell = m_testMap.getCell(n);
            cell.setFloorTile(SpriteManager::getSingleton().getSpriteKey("Tiles.Grass"));
        }

        for (int i = 0; i < m_testMap.getWidth() - 1; i++)
        for (int j = 0; j < m_testMap.getHeight() - 1; j++)
        {
            LocationMapNode & node = m_testMap.getNode(Point(i, j));
            
            float nodeHeight = (float)(rand() % 6);
            unsigned char randColor = rand() % 16;

            node.setHeight(nodeHeight);
            node.setColor(Color(32 + nodeHeight * 8 + randColor, 32 + nodeHeight * 8 + randColor, 32 + nodeHeight * 8 + randColor, 255));
        }

        m_testMap.setAmbientLight(Color(64, 64, 64, 0));

        Light light;
        light.setComponents(255, 255, 255, 0);
        light.setRange(200);
        light.setMapPos(Vector2(320.f, 200.f));
        light.enable(true);
        m_testMap.addLight(light);

        LocationMapCell & cell = m_testMap.getCell(Point(8, 6));
        cell.blockMovement(true);

        // TMP
        m_mapRenderer.init(m_renderSystem, Vector2(800.0f, 600.0f));
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

            Primitive cellCursor;
            Point tilePos = m_mouseMap.screenToTile(m_mousePos, m_mapRenderer.getScrollPos());
            Vector2 screenPos = TileBasics::getTileScreenPos(tilePos);
            DebugRenderingUtils::addTileBordersPrimitive(screenPos, Color::Yellow, cellCursor);

            // TMP
            DebugRenderingUtils::addTileBordersPrimitive(m_mousePos, Color::Red, cellCursor);

            cellCursor.draw(m_renderSystem);
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