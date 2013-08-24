#pragma once

/// @file Widget.hxx
/// @brief Widget, a base class for all UI elements.

#include <string>
#include <list>
#include "Serialization/Serializeable.hxx"
#include "Types/Vector2.hxx"
#include "Types/Color.hxx"
#include "Types/Rect.hxx"
#include "Input/Buttons.hxx"

namespace Core4
{
    /// Base class for all UI elements.
    class Widget
    {
    protected:
        Widget();
        Widget(const Widget &);
    public:
        /// Set position relative to parent.
        /// @param pos Position, in pixels.
        void setPos(const Vector2 & pos);

        /// Set size.
        /// @param size Size, in pixels.
        void setSize(const Vector2 & size);

        /// Dtor. Deletes all child widgets.
        virtual ~Widget();

        /// Is it visible?
        /// Widget is not visible by default.
        /// @return Yes/No.
        bool isVisible() const;

        /// Toggle widget visibility.
        /// @param visible Visibility flag.
        void setVisible(bool visible);

        /// Recursively render this widget and all its children.
        void renderTree();

        /// Render this widget.
        /// @param upperLeft Upper left corner position at screen, in pixels.
        virtual void render(const Vector2 & upperLeft);

        /// Find topmost clickable child widget.
        /// @param screenPos Screen position, in pixels.
        /// @return Widget pointer or NULL if not found.
        Widget * findClickableChild(const Vector2 & screenPos);

        /// Get upper left corner position at screen, in pixels.
        /// @return Upper left corner position.
        const Vector2 getScreenPos() const;

        /// Set widget color. Widgets are white by default.
        /// @param color Color.
        void setColor(const Color & color);

        /// Get widget color.
        /// @return Color.
        const Color & getColor() const;

        /// Get widget rectangle in screen coords.
        /// @return Widget rectangle in screen coords.
        Rect getScreenRect() const;

        /// is it clickable?
        /// Widgets are clickable by default.
        /// @return True if clickable.
        virtual bool isClickable();

        /// Character typed event handler.
        /// @param c Keyboard character.
        virtual void onChar(wchar_t c);

        /// Key pressed event handler.
        /// @param key A key.
        virtual void onKeyDown(const Buttons::Type key);
        
        /// Key released event handler.
        /// @param key A key.
        virtual void onKeyUp(const Buttons::Type key);
        
        /// Mouse movement event handler.
        /// @param mousePos Mouse position
        virtual void onMouseMove(const Vector2 & mousePos);
        
        /// Input focus event handler.
        virtual void onFocus();
        
        /// Input "de-focus" event handler.
        virtual void onDeFocus();

        /// Create child widget.
        /// @return Child widget pointer.
        template <typename T> T * createChild()
        {
            Widget * w = new T();
            w->m_parent = this;
            m_children.push_back(w);
        }

        /// Destroy child widget.
        void destroyChild(Widget * widget);
    protected:
        bool               m_visible;
        Rect               m_rect; // Rectangle is relative to widget's parent
        Widget *           m_parent;
        std::list<Widget*> m_children;
        Color              m_color;
    };

} // namespace Core4
