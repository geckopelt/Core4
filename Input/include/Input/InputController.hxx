#pragma once

#include <set>
#include "Utils/Singleton.hxx"
#include "Input/IInputListener.hxx"

/// @file InputController.hxx
/// @brief A user input controller class.

namespace Core4
{
    /// An input controller class.
    class InputController : public IInputListener, public Singleton<InputController>
    {
    public:
        /// @see IInputListener
        void onKeyDown(const Buttons::Type & button);

        /// @see IInputListener
        void onKeyUp(const Buttons::Type & button);

        /// @see IInputListener        
        void onMouseMove(const Vector2 & mousePos);

        /// Subscribe an input listener.
        void subscribe(IInputListener * listener);

        /// Unubscribe an input listener.
        void unsubscribe(IInputListener * listener);
    private:
        std::set<IInputListener*> m_listeners;
    };
} // namespace Core4

