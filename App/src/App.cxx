#include "App.hxx"
#include "Logging/LogHelpers.hxx"
#include "Configuration/Configuration.hxx"
#include "Image/FakeImageLoader.hxx"
#include "Serialization/Serializeable.hxx" // TODO: once again!
#include "Render/Circle.hxx"
#include "Facade/EngineFacade.hxx"
#include "UI/Font/FontManager.hxx"
#include "UI/UserInterfacePrimitives.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    App::App() : m_prevUpdate(0)
    {
    }

    //------------------------------------------------------------------------------
    App::~App()
    {
    }

    //------------------------------------------------------------------------------
    void App::init()
    {
        m_prevUpdate = getCurrTime();
        CORE4_LOG_SECTION("Creating RenderSystem");
        m_renderSystem = createRenderSystem();
        CORE4_LOG_MESSAGE("RenderSystem: " + m_renderSystem->getName());
        m_renderSystem->init(
            // TODO: rename into getScreen...()
            Configuration::getSingleton().screenWidth(),
            Configuration::getSingleton().screenHeight(),
            Configuration::getSingleton().getBpp(),
            Configuration::getSingleton().isWindowed());

        EngineFacade::getSingleton().init(m_renderSystem);

        // TMP!
        FontManager::getSingleton().addFont("Outlined", "Outlined.fnt");
        FontManager::getSingleton().addFont("Large", "LargeFont.fnt");
    }

    //------------------------------------------------------------------------------
    void App::render()
    {
        unsigned long currTime = getCurrTime();
        float dt = (float)(currTime - m_prevUpdate);
        m_prevUpdate = currTime;

        EngineFacade::getSingleton().updateAndRender(dt);

        // TMP
        Rect rect;
        rect.setUpperLeft(Vector2(100.0f, 50.0f));
        rect.setSize(Vector2(320.f, 200.0f));

        const Color coolColor(128, 128, 192, 255);
        UserInterfacePrimitives::renderWindow(m_renderSystem, rect, coolColor, L"A window");

        rect.setUpperLeft(Vector2(200.f, 100.f));
        rect.setSize(Vector2(100.f, 32.f));

        UserInterfacePrimitives::renderButton(m_renderSystem, rect, coolColor, L"A button", false);

        rect.setUpperLeft(Vector2(400.f, 100.f));
        UserInterfacePrimitives::renderButton(m_renderSystem, rect, coolColor, L"A button", true);

        // TMP
        UserInterfacePrimitives::renderSimpleText(m_renderSystem, Vector2(100.f, 100.f), 
            Color::White, "Outlined", L"This is your life, and it's ending one minute at a time");

        UserInterfacePrimitives::renderSimpleText(m_renderSystem, Vector2(100.f, 131.f), 
            Color::Red, "Outlined", L"Попробуй этих вкусных французских булок, да выпей чаю, %USERNAME%. 1234567890");

        UserInterfacePrimitives::renderSimpleText(m_renderSystem, Vector2(10.f, 181.f), 
            Color::White, "Large", L"Load Game, Save Game, Настройки");

        m_renderSystem->render();
    }
    
    //------------------------------------------------------------------------------
    void App::deinit()
    {
        EngineFacade::getSingleton().cleanup();

        if (NULL != m_renderSystem)
        {
            m_renderSystem->cleanup();
            delete m_renderSystem;
            m_renderSystem = NULL;
        }
        // TODO: dump masks memory
    }
} // namespace Core4