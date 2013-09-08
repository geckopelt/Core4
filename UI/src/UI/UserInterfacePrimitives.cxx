#include "Image/FakeImageLoader.hxx"
#include "Render/Primitive.hxx"
#include "UI/UserInterfacePrimitives.hxx"
#include "UI/Font/FontManager.hxx"
#include "Image/TargaLoader.hxx"
#include "Configuration/Configuration.hxx"

namespace Core4
{
    namespace
    {
        //------------------------------------------------------------------------------
        ITexture * getUiTexture(IRenderSystem * renderSystem)
        {
            // TODO: rename into "SolidColorImageLoader"
            // TODO: add UI Color Scheme
            static const Color transparentUiColor(255, 255, 255, 128);
            static const std::string TextureName("__uiTexture");
            static FakeImageLoader loader(transparentUiColor);
            return renderSystem->getTexture(TextureName, &loader);
        }

        //------------------------------------------------------------------------------
        Color modifyColor(const Color & color, float m)
        {
            float red   = color.red() * m;
            float green = color.green() * m;
            float blue  = color.blue() * m;
            if (red > 255) red = 255;
            if (green > 255) green = 255;
            if (blue > 255) blue = 255;
            return Color(
                static_cast<unsigned char>(red),
                static_cast<unsigned char>(green),
                static_cast<unsigned char>(blue),
                color.alpha());
        }
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderFilledRect(IRenderSystem * renderSystem, const Rect & rect, const Color & color)
    {
        const Vector2 & upperLeft = rect.getUpperLeft();
        const Vector2 & size = rect.getSize();

        IRenderSystem::Sprite sprite;
        sprite.alpha = true;
        sprite.width = size.x();
        sprite.height = size.y();
        for (size_t i = 0; i < IRenderSystem::NumCorners; i++)
        {
            sprite.diffuse[i] = color;
        }
        renderSystem->drawSprite(upperLeft.x(), upperLeft.y(), sprite, getUiTexture(renderSystem));
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderPanel(IRenderSystem * renderSystem, const Rect & rect, const Color & color)
    {
        const float ShadowOffset = 8.0f;
        const float ShadowFactor = 0.5f;

        Rect shadowRect(rect);
        shadowRect += Vector2(ShadowOffset, ShadowOffset);

        renderFilledRect(renderSystem, shadowRect, modifyColor(color, ShadowFactor));
        renderFilledRect(renderSystem, rect, color);
        renderFrame(renderSystem, rect, color);
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderFrame(IRenderSystem * renderSystem, const Rect & rect, const Color & color)
    {
        Primitive primitive;

        const Vector2 & upperLeft = rect.getUpperLeft();
        const Vector2 & size = rect.getSize();
        float x = upperLeft.x();
        float y = upperLeft.y();
        float width = size.x();
        float height = size.y();

        primitive.addLine(Primitive::Line(x, y, x + width, y, color));
        primitive.addLine(Primitive::Line(x + width, y, x + width, y + height, color));
        primitive.addLine(Primitive::Line(x, y + height, x + width, y + height, color));
        primitive.addLine(Primitive::Line(x, y, x, y + height, color));
        primitive.draw(renderSystem);
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderSimpleText(
        IRenderSystem * renderSystem, 
        const Vector2 & pos, 
        const Color & color, 
        const std::string & fontName, 
        const std::wstring & text)
    {
        // TODO: this code is experimental!

        const wchar_t DefaultChar(L'?');

        // TODO: optimize for texture switching
        // TODO: refactor, pre-create sprite lists

        const Font & font = FontManager::getSingleton().getFont(fontName);
        const Font::FontChars & chars = font.getChars();
        const FontPages & pages = font.getPages();
        const FontKerningInfo & kerning = font.getKerningInfo();

        // TODO: UGLY
        TargaLoader loader;

        // TMP: most stupid algorithm
        Vector2 currentPos(pos);
        for (size_t i = 0; i < text.size(); i++)
        {
            wchar_t currentChar = text.at(i);

            Font::FontChars::const_iterator it = chars.find(currentChar);
            if (it != chars.end())
            {
                const FontChar & c = it->second; 
                size_t pageNumber = c.getPageNumber();
                FontPages::const_iterator pagesIt = pages.find(pageNumber);
                CORE4_CHECK(pagesIt != pages.end(), "Unknown font page number");

                // TMP!!
                const std::string & textureName = Configuration::getSingleton().getResourcesRoot() + "/textures/" + pagesIt->second;
                ITexture * texture = renderSystem->getTexture(textureName, &loader);

                const Vector2 & upperLeft = c.getRect().getUpperLeft();
                const Vector2 & size = c.getRect().getSize();
                const Vector2 & offset = c.getOffset();

                IRenderSystem::Sprite sprite;
                sprite.alpha = true;
                sprite.bitmapX = upperLeft.x();
                sprite.bitmapY = upperLeft.y();
                sprite.width = size.x();
                sprite.height = size.y();

                for (size_t j = 0; j < IRenderSystem::NumCorners; j++)
                {
                    sprite.diffuse[j] = color;
                }

                float kerningAmount = (i < text.size() - 1) ? kerning.getKerning(currentChar, text.at(i + 1)) : 0.f;

                renderSystem->drawSprite(currentPos.x() + offset.x(), currentPos.y() + offset.y(), sprite, texture);
                currentPos.setX(currentPos.x() + c.getAdvanceX() + kerningAmount);
            }
        }
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderText(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::string & fontName, const std::wstring & text)
    {
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderButton(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::wstring & text, bool pushed)
    {
        Primitive primitive;

        const float LighterFactor = 1.2f;
        const float DarkerFactor = 0.8f;
        const Color LighterColor = modifyColor(color, LighterFactor);
        const Color DarkerColor  = modifyColor(color, DarkerFactor);

        const Vector2 & upperLeft = rect.getUpperLeft();
        const Vector2 & size = rect.getSize();
        float x = upperLeft.x();
        float y = upperLeft.y();
        float width = size.x();
        float height = size.y();

        const size_t Thickness(2);

        renderFilledRect(renderSystem, rect, color);

        for (size_t i = 0; i < Thickness; i++)
        {
            primitive.addLine(Primitive::Line(x + i, y + i, x + width - i, y + i, pushed ? DarkerColor : LighterColor));
            primitive.addLine(Primitive::Line(x + i, y + i, x + i, y + height - 1, pushed ? DarkerColor : LighterColor));
            primitive.addLine(Primitive::Line(x + width - i, y + i, x + width - i, y + height - i, pushed ? LighterColor :  DarkerColor));
            primitive.addLine(Primitive::Line(x + i, y + height - i, x + width - i, y + height - i, pushed ? LighterColor :  DarkerColor));
        }
        primitive.draw(renderSystem);
    }

    //------------------------------------------------------------------------------
    void UserInterfacePrimitives::renderWindow(IRenderSystem * renderSystem, const Rect & rect, const Color & color, const std::wstring & caption)
    {
        const float HeaderHeight(32);
        const float HeaderColorFactor = 0.7f;

        Rect headerRect(rect);
        headerRect.setSize(Vector2(rect.getSize().x(), HeaderHeight));

        renderPanel(renderSystem, rect, color);
        renderFilledRect(renderSystem, headerRect, modifyColor(color, HeaderColorFactor));
        renderFrame(renderSystem, headerRect, color);
    }
}