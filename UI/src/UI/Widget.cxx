#include <algorithm>
#include "Utils/Guards.hxx"
#include "UI/Widget.hxx"
#include "UI/UI.hxx"

namespace Core4
{
    //-------------------------------------------------------------------------------------------------------
    Widget::Widget() : m_visible(false), m_parent(NULL)
    {
        m_color = Color::White;
    }

    //-------------------------------------------------------------------------------------------------------
    Widget::~Widget()
    {
        // Sort of a hack
        if (this == UI::getSingleton().getFocus())
        {
            UI::getSingleton().setFocus(NULL);
        }
        for (std::list<Widget*>::iterator it = m_children.begin(); it != m_children.end(); it++)
        {
            Widget * child = (*it);
            if (NULL != child)
                delete child;
        }
    }

    //-------------------------------------------------------------------------------------------------------
    void Widget::setPos(const Vector2 & pos)
    {
        m_rect.setUpperLeft(pos);
    }

    //-------------------------------------------------------------------------------------------------------
    void Widget::setSize(const Vector2 & size)
    {
        m_rect.setSize(size);
    }

    //-------------------------------------------------------------------------------------------------------
    void Widget::setVisible(bool visible)
    {
        m_visible = visible;
    }

    //-------------------------------------------------------------------------------------------------------
    bool Widget::isVisible() const
    {
        return m_visible;
    }

    //--------------------------------------------------------------------------------------------
    Widget * Widget::findClickableChild(const Vector2 & screenPos)
    {
        for (std::list<Widget*>::iterator it = m_children.begin(); it != m_children.end(); it++)
        {
            Widget * child = (*it);

            if (NULL == child)
                continue;

            Widget * found = child->findClickableChild(screenPos);
            if (NULL != found)
                return found;
        }

        Rect absRect = m_rect;
        absRect.setUpperLeft(getScreenPos());
        if (isVisible() && absRect.pointInside(screenPos) && isClickable())
        {
            return this;
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------
    const Vector2 Widget::getScreenPos() const
    {
        Vector2 screenPos = m_rect.getUpperLeft();
        if (NULL != m_parent)
        {
            screenPos += m_parent->getScreenPos();
        }
        return screenPos;
    }

    //--------------------------------------------------------------------------------------------
    void Widget::renderTree()
    {
        if (!isVisible())
            return;
        render(getScreenPos());
        for (std::list<Widget*>::iterator it = m_children.begin(); it != m_children.end(); it++)
        {
            Widget * child = (*it);
            if (NULL != child)
                child->renderTree();
        }
    }

    //--------------------------------------------------------------------------------------------
    void Widget::render(const Vector2 & upperLeft)
    {
    }

    //--------------------------------------------------------------------------------------------
    void Widget::setColor(const Color & color)
    {
        m_color = color;
    }

    //--------------------------------------------------------------------------------------------
    const Color & Widget::getColor() const
    {
        return m_color;
    }

    //--------------------------------------------------------------------------------------------
    Rect Widget::getScreenRect() const
    {
        Rect rc = m_rect;
        rc.setUpperLeft(getScreenPos());
        return rc;
    }

    //--------------------------------------------------------------------------------------------
    bool Widget::isClickable()
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------
    void Widget::onChar(wchar_t c)
    {
    }

    //--------------------------------------------------------------------------------------------
    void Widget::onKeyDown(const Buttons::Type key)
    {
    }
        
    //--------------------------------------------------------------------------------------------
    void Widget::onKeyUp(const Buttons::Type key)
    {
    }
        
    //--------------------------------------------------------------------------------------------
    void Widget::onMouseMove(const Vector2 & mousePos)
    {
    }
        
    //--------------------------------------------------------------------------------------------
    void Widget::onFocus()
    {
    }
       
    //--------------------------------------------------------------------------------------------
    void Widget::onDeFocus()
    {
    }

    //--------------------------------------------------------------------------------------------
    void Widget::destroyChild(Widget * widget)
    {
        CORE4_CHECK(NULL != widget, "Child is NULL");
        std::list<Widget*>::iterator it = std::find(m_children.begin(), m_children.end(), widget);
        CORE4_CHECK(it != m_children.end(), "Unknown child");
        Widget * w = (*it);
        delete w;
        m_children.erase(it);
    }
} // namespace Core4
