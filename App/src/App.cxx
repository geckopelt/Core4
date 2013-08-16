#include "App.hxx"
#include "Logging/LogHelpers.hxx"
#include "Configuration/Configuration.hxx"
#include "Image/FakeImageLoader.hxx"
#include "Render/Circle.hxx"

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
            // TODO: rename into getScreen...()
            Configuration::getSingleton().screenWidth(),
            Configuration::getSingleton().screenHeight(),
            Configuration::getSingleton().getBpp(),
            Configuration::getSingleton().isWindowed());

        // $TMP
        m_testTexture = m_renderSystem->getTexture("foo", &FakeImageLoader(Color(255, 0, 0, 128))); 
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
            m_renderSystem->clearScreen(Color(255, 255, 255, 255));

            IRenderSystem::Sprite sprite;
            sprite.bitmapX = 0;
            sprite.bitmapY = 0;
            sprite.width = 64;
            sprite.height = 32;
            sprite.alpha = true;

            float heights[4];

            for (int i = 0; i < 4; i++)
            {
                sprite.diffuse[i] = Color(255, 255, 255, 64);
                sprite.specular[i] = Color(255, 255, 255, 255);
                heights[i] = 0.0f;
            }
            m_renderSystem->drawSprite(100.0f, 100.0f, sprite, m_testTexture);
            m_renderSystem->drawSprite(132.0f, 116.0f, sprite, m_testTexture);
            
            sprite.alpha = false;

            m_renderSystem->drawIsoTile(200.0f, 200.0f, sprite, heights, m_testTexture);

            IRenderSystem::PrimitivePoint start;
            start.x = 10.0f;
            start.y = 20.0f;
            start.color = Color::Red;

            IRenderSystem::PrimitivePoint end;
            end.x = 50.0f;
            end.y = 50.0f;
            end.color = Color::Green;

            m_renderSystem->drawLine(start, end);

            Circle(320.f, 200.f, 128.f, Color::Yellow).draw(m_renderSystem);
            Circle(320.f, 200.f, 63.f, Color(0, 255, 0, 128)).draw(m_renderSystem);
            Circle(320.f, 200.f, 32.f, Color::Blue).draw(m_renderSystem);

            m_renderSystem->render();
        }
    }
    
    //------------------------------------------------------------------------------
    void App::deinit()
    {
        m_renderSystem->cleanup();
        delete m_renderSystem;
        m_renderSystem = NULL;
        // TODO: dump masks memory
    }
} // namespace Core4