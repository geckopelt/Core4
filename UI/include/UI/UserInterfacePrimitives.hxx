#pragma once

/// @file UserInterfacePrimitives.hxx
/// @brief UI Primitives helper

#include <string>
#include "Types/Rect.hxx"
#include "Types/Vector2.hxx"
#include "Types/Color.hxx"
#include "UI/Widget.hxx"
#include "Render/IRenderSystem.hxx"

namespace Core4
{
    /// UI primitives.
    struct UserInterfacePrimitives
    {
        /// Render a rectangle filled with color.
        /// @param renderSystem Render system to use.
        /// @param rect Dimensions and position, in pixels.
        /// @param color Color.
        static void renderFilledRect(IRenderSystem * renderSystem, const Rect & rect, const Color & color);

        /// Render a simple "panel".
        /// @param renderSystem Render system to use.
        /// @param rect Dimensions and position, in pixels.
        /// @param color Color.
        static void renderPanel(IRenderSystem * renderSystem, const Rect & rect, const Color & color);

        /// Render a simple rectangular frame.
        /// @param renderSystem Render system to use.
        /// @param rect Dimensions and position, in pixels.
        /// @param color Color.
        static void renderFrame(IRenderSystem * renderSystem, const Rect & rect, const Color & color);

        /// Render text string.
        /// @param renderSystem Render system to use.
        /// @param pos Screen position, in pixels.
        /// @param color Color.
        /// @param text Text.
        static void renderSimpleText(IRenderSystem * renderSystem, const Vector2 & pos, const Color & color, const std::wstring & text);

        /// Render a text box.
        /// @param renderSystem Render system to use.
        /// @param rect Rectangular area to contain the text.
        /// @param color Color.
        /// @param text Text.
        static void renderText(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::wstring & text);

        /// Render a button.
        /// @param renderSystem Render system to use.
        /// @param rect Dimensions and position, in pixels.
        /// @param color Color.
        /// @param text Button text.
        /// @param clicked Is it "pushed"?
        static void renderButton(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::wstring & text, bool pushed);

        /// Render a window. A window is a panel with caption at top.
        /// @param renderSystem Render system to use.
        /// @param rect Dimensions and position, in pixels.
        /// @param color Color.
        /// @param text Caption text.
        static void renderWindow(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::wstring & caption);
    };
}