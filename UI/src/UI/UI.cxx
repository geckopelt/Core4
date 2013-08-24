#include "Sprites/SpriteManager.hxx"
#include "UI/UI.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------
    UI::UI() : m_focus(NULL), m_cursorSprite(ISpriteManager::InvalidSpriteKey),   m_cursorShown(false)
    {
        setVisible(true);
    }

    //--------------------------------------------------------------------------------------------
    void UI::render(const Vector2 & upperLeft)
    {
    }

    //--------------------------------------------------------------------------------------------
    void UI::render(IRenderSystem * renderSystem)
    {
        renderTree();
        const size_t frame = m_animation.getCurrentFrame();
        if (m_cursorShown)
        {
            const Sprite & sprite    = SpriteManager::getSingleton().getSprite(m_cursorSprite);
            const Vector2 & mousePos = getMousePos();
            renderSystem->drawSprite(mousePos.x(), mousePos.y(), sprite.getFrame(m_animation.getCurrentFrame()).toRS(), sprite.getTexture());
        }
    }

    //--------------------------------------------------------------------------------------------
    bool UI::checkFocus() const
    {
        return (NULL != m_focus && this != m_focus);
    }

    //--------------------------------------------------------------------------------------------
    void UI::onKeyDown(const Buttons::Type button)
    {
        if (checkFocus())
        {
            m_focus->onKeyDown(button);
        }
    }

    //--------------------------------------------------------------------------------------------
    void UI::onKeyUp(const Buttons::Type button)
    {
        if (checkFocus())
        {
            m_focus->onKeyUp(button);
        }
    }

    //--------------------------------------------------------------------------------------------
    void UI::onChar(wchar_t c)
    {
        if (checkFocus())
        {
            m_focus->onChar(c);
        }
    }

    //--------------------------------------------------------------------------------------------
    void UI::onMouseMove(const Vector2 & mousePos)
    {
        m_mousePos = mousePos;
        setFocus(findClickableChild(mousePos));
        if (checkFocus())
        {
            m_focus->onMouseMove(mousePos);
        }
    }

    //--------------------------------------------------------------------------------------------
    const Vector2 & UI::getMousePos() const
    {
        return m_mousePos;
    }

    //--------------------------------------------------------------------------------------------
    void UI::showCursor(bool show)
    {
        m_cursorShown = show;
    }

    //--------------------------------------------------------------------------------------------
    Animation & UI::getCursorAnimation()
    {
        return m_animation;
    }

    //--------------------------------------------------------------------------------------------
    void UI::update(float dt)
    {
        m_animation.update(dt);
    }

    //--------------------------------------------------------------------------------------------
    void UI::setCursor(const ISpriteManager::SpriteKey & spriteKey)
    {
        m_cursorSprite = spriteKey;
        m_animation.setup(m_cursorSprite);
    }

    //--------------------------------------------------------------------------------------------
    void UI::setCursorRefPoint(const Vector2 & pt)
    {
        m_mouseRef = pt;
    }

    //--------------------------------------------------------------------------------------------
    Widget * UI::getFocus()
    {
        return m_focus;
    }

    //--------------------------------------------------------------------------------------------
    void UI::setFocus(Widget * focus)
    {
        if (NULL != m_focus) 
            m_focus->onDeFocus();
        m_focus = focus;
        if (NULL != m_focus) 
            m_focus->onFocus();
    }
} // namespace Core4
