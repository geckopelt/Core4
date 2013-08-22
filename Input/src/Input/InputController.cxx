#include "Serialization/Serializeable.hxx" // TODO: hack. Get rid of this stupid serialization implementation!
#include "Input/InputController.hxx"
#include "Types/Vector2.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------------------------------------
    void InputController::onKeyDown(const Buttons::Type & button)
    {
        for (std::set<IInputListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++)
        {
            (*it)->onKeyDown(button);
        }
    }

    //------------------------------------------------------------------------------------------------------------
    void InputController::onKeyUp(const Buttons::Type & button)
    {
        for (std::set<IInputListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++)
        {
            (*it)->onKeyUp(button);
        }
    }

    //------------------------------------------------------------------------------------------------------------
    void InputController::onMouseMove(const Vector2 & mousePos)
    {
        for (std::set<IInputListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++)
        {
            (*it)->onMouseMove(mousePos);
        }
    }

    //------------------------------------------------------------------------------------------------------------
    void InputController::subscribe(IInputListener * listener)
    {
        m_listeners.insert(listener);
    }

    //------------------------------------------------------------------------------------------------------------
    void InputController::unsubscribe(IInputListener * listener)
    {
        m_listeners.erase(listener);
    }
} // namespace Core4