#pragma once

/// @file UI.hxx
/// @brief Root GUI element 

#include "Utils/Singleton.hxx"
#include "UI/Widget.hxx"
#include "Render/IRenderSystem.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Sprites/Animation.hxx"

namespace Core4
{
    /// A root GUI element. Visible by default.
    class UI : public Widget, public Singleton<UI>
    {
    public:
        /// Ctor.
        UI();

        /// @see Widget
        void render(const Vector2 & upperLeft);

        /// @see Widget
        void onChar(wchar_t c);

        /// @see Widget
        void onKeyDown(const Buttons::Type key);
        
        /// @see Widget
        void onKeyUp(const Buttons::Type key);
        
        /// @see Widget
        void onMouseMove(const Vector2 & mousePos);

        /// Get mouse position.
        const Vector2 & getMousePos() const;

        /// Whether to show mouse cursor.
        /// @param show Cursor visibility flag.
        void showCursor(bool show);

        /// Get cursor animation reference.
        /// @return Cursor animation reference.
        Animation & getCursorAnimation();

        /// Update UI.
        void update(float dt);

        /// Set cursor sprite.
        /// @param spriteKey Sprite key.
        void setCursor(const ISpriteManager::SpriteKey & spriteKey);

        /// Render everything.
        /// @param renderSystem Render system to use.
        void render(IRenderSystem * renderSystem);

        /// Set mouse cursor reference point.
        /// @param pt Cursor reference point.
        void setCursorRefPoint(const Vector2 & pt);

        /// Get current input focus.
        /// @return Widget pointer or NULL.
        Widget * getFocus();

        /// Set current input focus.
        /// @param focus Widget pointer.
        void setFocus(Widget * focus);
    private:
        bool checkFocus() const;

        Widget *                  m_focus;
        Vector2                   m_mousePos;
        Vector2                   m_mouseRef;
        Animation                 m_animation;
        ISpriteManager::SpriteKey m_cursorSprite;
        bool                      m_cursorShown;
    };
} // namespace Core4
