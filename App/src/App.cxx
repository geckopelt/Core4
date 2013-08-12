#include "App.hxx"
#include "Logging/LogHelpers.hxx"
#include "Configuration/Configuration.hxx"
#include "Image/FakeImageLoader.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    App::App() : m_prevUpdate(0), m_testTexture(NULL)
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
            Configuration::getSingleton().screenWidth(),
            Configuration::getSingleton().screenHeight(),
            Configuration::getSingleton().getBpp(),
            Configuration::getSingleton().isWindowed());

        // $TMP
        m_testTexture = m_renderSystem->createTexture("foo", &FakeImageLoader(Color(255, 0, 0, 255))); 
    }

    //------------------------------------------------------------------------------
    void App::render()
    {
        unsigned long currTime = getCurrTime();
        float dt = (float)(currTime - m_prevUpdate);
        // TODO: update Engine with dt 
        m_prevUpdate = currTime;
        // TODO: call Engine::render()
        if (NULL != m_renderSystem)
        {
            // TODO: this code is temporary of course
            m_renderSystem->clearScreen(Color(32, 32, 32, 255));

            IRenderSystem::Sprite sprite;
            sprite.bitmapX = 0;
            sprite.bitmapY = 0;
            sprite.width = 64;
            sprite.height = 32;
            sprite.alpha = false;

            float heights[4];

            for (int i = 0; i < 4; i++)
            {
                sprite.diffuse[i] = Color(255, 255, 255, 255);
                sprite.specular[i] = Color(255, 255, 255, 255);
                heights[i] = 0.0f;
            }
            m_renderSystem->drawSprite(100.0f, 100.0f, sprite, m_testTexture);
            m_renderSystem->drawIsoTile(200.0f, 200.0f, sprite, heights, m_testTexture);

            m_renderSystem->render();
        }
    }
    
    //------------------------------------------------------------------------------
    void App::deinit()
    {
        // TMP!
        delete m_testTexture;

        m_renderSystem->cleanup();
        delete m_renderSystem;
        m_renderSystem = NULL;
        // TODO: dump masks memory
    }
} // namespace Core4