#include "App.hxx"
#include "Logging/LogHelpers.hxx"
#include "Configuration/Configuration.hxx"

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
    }

    //------------------------------------------------------------------------------
    void App::render()
    {
        unsigned long currTime = getCurrTime();
        float dt = (float)(currTime - m_prevUpdate);
        // TODO: update Engine with dt 
        m_prevUpdate = currTime;
        // TODO: call Engine::render()
    }
    
    //------------------------------------------------------------------------------
    void App::deinit()
    {
        // TODO: dump masks memory
    }
} // namespace Core4