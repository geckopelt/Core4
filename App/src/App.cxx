#include "App.hxx"
#include "Logging/LogHelpers.hxx"
#include "Configuration/Configuration.hxx"
#include "Image/FakeImageLoader.hxx"
#include "Serialization/Serializeable.hxx" // TODO: once again!
#include "Render/Circle.hxx"
#include "Facade/EngineFacade.hxx"

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
    }

    //------------------------------------------------------------------------------
    void App::render()
    {
        unsigned long currTime = getCurrTime();
        float dt = (float)(currTime - m_prevUpdate);
        m_prevUpdate = currTime;
        EngineFacade::getSingleton().updateAndRender(dt);
    }
    
    //------------------------------------------------------------------------------
    void App::deinit()
    {
        EngineFacade::getSingleton().cleanup();
        m_renderSystem->cleanup();
        delete m_renderSystem;
        m_renderSystem = NULL;
        // TODO: dump masks memory
    }
} // namespace Core4