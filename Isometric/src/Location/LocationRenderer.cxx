#include "Location/LocationRenderer.hxx"
#include "Tiles/TileBasics.hxx"
#include "Debug/DebugRenderer.hxx"

namespace Core4
{
    namespace
    {
        /// Magical Fast Inverse Square Root (Carmack's Reverse)
        float invSqrt(float x)
        {
            float halfX = x * .5f;
            int i = *(int*)&x;
            i = 0x5f375a86 - (i >> 1);
            x = *(float*)&i;
            x = x * (1.5f - halfX * x * x);
            return x;
        }

        void normalizeColorComponent(int & cc)
        {
            if (cc < 0)
                cc = 0;
            else
            if (cc > 255)
                cc = 255;
        }
    }

    const float DefaultGamma = 1.f;

    //------------------------------------------------------------------------------------------------------------
    LocationRenderer::LocationRenderer() :
        m_renderSystem(NULL),
        m_locationMap(NULL),
        m_showBlockedTiles(false),
        m_fogDensity(0.0f),
        m_fogEnabled(false),
        m_gamma(DefaultGamma),
        m_debugRenderer(NULL)
    {
        m_backgroundColor = Color::DarkGray;
    }

    //------------------------------------------------------------------------------------------------------------
    LocationRenderer::~LocationRenderer()
    {
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::init(IRenderSystem * renderSystem, const Vector2 & screenSize)
    {
        m_renderSystem = renderSystem;
        m_screenAnchor.setX(TileBasics::TileWidth);
        m_screenAnchor.setY(TileBasics::TileHeight);
        m_screenSpace.setSize(screenSize);

        // TMP
        m_debugRenderer = new DebugRenderer();
    }

    // TODO: get rid of warnings

    // TODO: this old code is still to be refactored

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::render()
    {
        m_objectBounds.clear();

        if (NULL == m_locationMap)
            return;

        if (NULL != m_debugRenderer)
            m_debugRenderer->onNewFrame();

        const size_t locationWidth  = m_locationMap->getWidth();
        const size_t locationHeight = m_locationMap->getHeight();

        // Approximate light values lookup
        const size_t numTiles = locationWidth * locationHeight;
        if (m_approxCellLighting.size() != numTiles) 
            m_approxCellLighting.resize(numTiles);

        int mapX = int(m_screenAnchor.x() / TileBasics::TileWidth);
	    int mapY = int(m_screenAnchor.y() / TileBasics::TileHeight);

        // // TODO: calculate once
        const int tileColsPerScreen = static_cast<int>(m_screenSpace.getSize().x()) / TileBasics::TileWidth + 1;
        const int tileRowsPerScreen = static_cast<int>(m_screenSpace.getSize().y()) / (TileBasics::TileHeight / 2) + 1;

	    Vector2 tilePos;

	    int maxY = mapY + tileRowsPerScreen + 6; // TODO: get rid of magic number
	    if (maxY > locationHeight - 1)
	        maxY = locationHeight - 1;

        int startX = mapX + tileColsPerScreen + 1;
        if (startX > (int)locationWidth - 1)
                startX = (int)locationWidth - 1;

        int endX = mapX - 1;
        if (endX < 0)
            endX = 0;

        // Draw tiles
	    for (int y = mapY; y <= maxY; y++)
	    for (int x = startX; x >= endX; x--)
	    {
	        const LocationMapCell & cell = m_locationMap->getCell(Point(x, y));
            const ISpriteManager::SpriteKey & spriteKey = cell.getSpriteKey();
            if (ISpriteManager::InvalidSpriteKey != spriteKey)
		    {
                tilePos = TileBasics::getTileScreenPos(Point(x, y));
		        tilePos = worldToScreen(tilePos);

                std::vector<float> heights;
                m_locationMap->getCellHeights(Point(x, y), heights);

                const Sprite & sprite = SpriteManager::getSingleton().getSprite(spriteKey);
		        IRenderSystem::Sprite spriteToRender = sprite.getFrame(0).toRS();

                const float offsetsX[IRenderSystem::NumCorners] = 
                { 
                    TileBasics::TileWidth / 2.f, 
                    0.f, 
                    TileBasics::TileWidth, 
                    TileBasics::TileWidth / 2.f 
                };
		        
                const float offsetsY[IRenderSystem::NumCorners] = 
                { 
                    0.f, 
                    TileBasics::TileHeight / 2.f, 
                    TileBasics::TileHeight / 2.f, 
                    TileBasics::TileHeight 
                };

		        const Vector2 & worldPos = screenToWorld(tilePos);

                // Calculate average lighting
		        int avgR(0), avgG(0), avgB(0), avgF(0);
                for (size_t i = 0; i < IRenderSystem::NumCorners; i++)
		        {
                    const Color & base = m_locationMap->getNode(m_locationMap->getNodePos(Point(x, y), i)).getColor();

		            int r(0), g(0), b(0), f(0);
                    Color calculated;
		            calcLightsAtPoint(Vector2(worldPos.x() + offsetsX[i], worldPos.y() + offsetsY[i]), calculated);

		            r += base.red();
		            g += base.green();
		            b += base.blue();
		            f += base.alpha();

                    // TODO: ugly
                    normalizeColorComponent(r);
                    normalizeColorComponent(g);
                    normalizeColorComponent(b);
                    normalizeColorComponent(f);

                    spriteToRender.diffuse[i]  = modifyWithGamma(Color(r, g, b, 255));

                    // TODO: show blocked tile
                    /*
                    if (tile.blocksMovement && m_showBlockedTiles)
                    {
                        // TODO: render red diamond
                    }
                    */

                    f = (int)(float(f) * m_fogDensity);
                    spriteToRender.specular[i] = Color(0, 0, 0, f);
                    avgR += r;
                    avgG += g;
                    avgB += b;
                    avgF += f;
		        }

                // TODO: move approximate lighting into separate class!
		        m_approxCellLighting[y * locationWidth + x] = Color(avgR >> 2, avgG >> 2, avgB >> 2, avgF >> 2);
                m_renderSystem->drawIsoTile(tilePos.x(), tilePos.y(), spriteToRender, &heights[0], sprite.getTexture()); 

                if (NULL != m_debugRenderer)
                    m_debugRenderer->onTileRendered(tilePos, cell);

            }
	    }

        // TODO!
        if (NULL != m_debugRenderer)
            m_debugRenderer->onRender(m_renderSystem);
        
        // TODO: ensure LocationMap is updated first

        // Draw objects
	    for (int y = mapY; y <= maxY; y++)
	    for (int x = startX; x >= endX; x--)
	    {
            const LocationMap::ObjectIndexList & objects = m_locationMap->getObjectsAtCell(Point(x, y));
	        for (LocationMap::ObjectIndexList::const_iterator it = objects.begin(); it != objects.end(); it++)
            {
                tilePos = TileBasics::getTileScreenPos(Point(x, y));
		        tilePos = worldToScreen(tilePos);
                LocationMapObject & object = m_locationMap->getObjectByIndex(*it);

		        if (object.isVisible())
		        {
		            Animation & anim            = object.getAnimation();
                    const Sprite & sprite       = SpriteManager::getSingleton().getSprite(anim.getSpriteKey());
                    ITexture * texture          = sprite.getTexture();
                    IRenderSystem::Sprite frame = sprite.getFrame(anim.getCurrentFrame()).toRS();

                    const Color & own    = object.getColor();
                    const Color & approx = m_approxCellLighting.at(y * m_locationMap->getWidth() + x);

                    for (size_t i = 0; i < IRenderSystem::NumCorners; i++)
                    {
                        int r = approx.red()   + own.red();
                        int g = approx.green() + own.green();
                        int b = approx.blue()  + own.blue();
                        normalizeColorComponent(r);
                        normalizeColorComponent(g);
                        normalizeColorComponent(b);
                        frame.diffuse[i]  = modifyWithGamma(Color(r, g, b, 255));
                        frame.specular[i] = Color(0, 0, 0, approx.alpha());
                    }

                    float xpos = tilePos.x();
                    float ypos = tilePos.y();

                    xpos += ((TileBasics::TileWidth  - frame.width) / 2.f);
                    Vector2 tileOffset = object.getTileOffset();
                    xpos += tileOffset.x();
                    ypos += tileOffset.y();
                    ypos += TileBasics::TileHeight;
                    ypos -= (frame.height);

                    Vector2 objectPos(xpos, ypos);
                    m_renderSystem->drawSprite(objectPos.x(), objectPos.y(), frame, texture);
                    if (object.selectionEnabled())
                    {
                        BoundingBox bb;
                        bb.setRect(Rect(objectPos, Vector2(frame.width, frame.height)));
                        bb.setMapIndex(*it);
                        m_objectBounds.push_front(bb);
                    }
		        }
            }
	    }
    }
  
    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setLocationMap(LocationMap * locationMap)
    {
        m_locationMap = locationMap;
    }

    //------------------------------------------------------------------------------------------------------------
    const LocationMap * LocationRenderer::getLocationMap() const
    {
        return m_locationMap;
    }

    //------------------------------------------------------------------------------------------------------------
    const Vector2 & LocationRenderer::getScrollPos() const
    {
        return m_screenAnchor;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setScrollPos(const Vector2 & pos)
    {
        m_screenAnchor = pos;
        getScrollRect().normalizePoint(m_screenAnchor);
    }

    //------------------------------------------------------------------------------------------------------------
    const Vector2 LocationRenderer::screenToWorld(const Vector2 & screen)
    {
        float x = screen.x();
        float y = screen.y();
        x -= m_screenSpace.getUpperLeft().x();
        y -= m_screenSpace.getUpperLeft().y();
	    x += m_screenAnchor.x();
	    y += m_screenAnchor.y();
	    return Vector2(x, y);
    }

    //------------------------------------------------------------------------------------------------------------
    const Vector2 LocationRenderer::worldToScreen(const Vector2 & world)
    {
        float x = world.x();
        float y = world.y();
        x -= m_screenAnchor.x();
        y -= m_screenAnchor.y();
        x += m_screenSpace.getUpperLeft().x();
        y += m_screenSpace.getUpperLeft().y();
        return Vector2(x, y);
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setScreenSize(const Vector2 & size)
    {
        m_screenSpace.setSize(size);
    }

    //------------------------------------------------------------------------------------------------------------
    const Vector2 & LocationRenderer::getScreenSize() const
    {
        return m_screenSpace.getSize();
    }

    //------------------------------------------------------------------------------------------------------------
    const Rect LocationRenderer::getScrollRect() const
    {
        Rect rect;
        rect.setUpperLeft(Vector2(TileBasics::TileWidth / 2, TileBasics::TileHeight / 2.f));

        if (NULL != m_locationMap)
        {
            const Vector2 & screenSpaceSize = getScreenSize();

            float sizeX = (m_locationMap->getWidth() - 1)  * TileBasics::TileWidth + (TileBasics::TileWidth / 2.f) - screenSpaceSize.x();
            float sizeY = (m_locationMap->getHeight() - 1) * TileBasics::TileHeight / 2.f - screenSpaceSize.y();
            rect.setSize(Vector2(sizeX, sizeY));
        }
        return rect;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::showBlockedTiles(bool show)
    {
        m_showBlockedTiles = show;
    }

    //------------------------------------------------------------------------------------------------------------
    bool LocationRenderer::blockedTilesShown() const
    {
        return m_showBlockedTiles;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::renderSprite(const Vector2 & screenPos, const Sprite & sprite, const size_t frame) const
    {
        IRenderSystem::Sprite s = sprite.getFrame(frame).toRS();
        for (size_t i = 0; i < IRenderSystem::NumCorners; i++)
        {
            Color newColor(modifyWithGamma(s.diffuse[i]));
            s.diffuse[i] = newColor;
        }
        m_renderSystem->drawSprite(screenPos.x(), screenPos.y(), s, sprite.getTexture());
    }

    //------------------------------------------------------------------------------------------------------------
    LocationMapObject * LocationRenderer::getObjectAtPos(const Vector2 & screen)
    {
        /* TODO: implement TextureMaskManager
        for (std::list<BoundingBox>::const_iterator it = m_objectBounds.begin(); it != m_objectBounds.end(); it++)
        {
            const BoundingBox & bb = (*it);

            // Per-bbox check
            if (bb.getRect().pointInside(screen))
            {
                // Per-pixel check
                Object & obj                    = ACTS_SINGLE(World).getObject(bb.index);
                Animation & anim                = obj.getAnimation();
                
                const Sprite & sprite           = ACTS_SINGLE(SpriteManager).getSprite(anim.getSpriteIndex());
                const std::string & textureName = "textures/" + sprite.getTextureName(); // C4_GET_TEXTURE(sprite.getTextureName())->name(); // $TODO!
                TRS::IRender::Sprite trs        = sprite.getFrame(anim.getCurrentFrame()).toTRS();

                Vector2 texturePos(trs.bitmapX, trs.bitmapY); // $TODO CHECK

                texturePos.x += (screen.x - bb.rect.upperLeft.x);
                texturePos.y += (screen.y - bb.rect.upperLeft.y);

                if (0 != ACTS_SINGLE(TextureMaskManager).getMaskPixel(textureName, Point((int)texturePos.x, (int)texturePos.y)))
                    return (int)bb.index;
            }
        }
        return World::InvalidObjectIndex;
        */
        return NULL;
    }

    //------------------------------------------------------------------------------------------------------------
    const Color & LocationRenderer::getBackgroundColor() const
    {
        return m_backgroundColor;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setBackgroundColor(const Color & color)
    {
        m_backgroundColor = color;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::clearScreen()
    {
        m_renderSystem->clearScreen(modifyWithGamma(m_backgroundColor));
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::enableFog(bool enable)
    {
        m_renderSystem->fogEnable(enable);
        m_fogEnabled = enable;
    }

    //------------------------------------------------------------------------------------------------------------
    bool LocationRenderer::isFogEnabled() const
    {
        return m_fogEnabled;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setFogColor(const Color & color)
    {
        m_fogColor = color;
        m_renderSystem->setFogColor(color);
    }

    //------------------------------------------------------------------------------------------------------------
    const Color & LocationRenderer::getFogColor() const
    {
        return m_fogColor;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setFogDensity(float density)
    {
        m_fogDensity = density;
    }

    //------------------------------------------------------------------------------------------------------------
    float LocationRenderer::getFogDensity() const
    {
        return m_fogDensity;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::setGamma(float gamma)
    {
        m_gamma = gamma;
        setFogColor(modifyWithGamma(m_fogColor));
    }

    //------------------------------------------------------------------------------------------------------------
    float LocationRenderer::getGamma() const
    {
        return m_gamma;
    }

    //------------------------------------------------------------------------------------------------------------
    void LocationRenderer::calcLightsAtPoint(const Vector2 & world, Color & dest ) const
    {
        if (NULL == m_locationMap)
            return;

        const Color & ambient = m_locationMap->getAmbientLight();

        unsigned short red   = ambient.red();
        unsigned short green = ambient.green();
        unsigned short blue  = ambient.blue();
        unsigned short fog   = ambient.alpha();

        const SerializeableVector<Light> & lights = m_locationMap->getLights();
        for (SerializeableVector<Light>::const_iterator it = lights.begin(); it != lights.end(); it++)
        {
            const Light &   light    = (*it);

            if (!light.isEnabled())
                continue;

            const Vector2 & lightPos = light.getMapPos();
            float distX = world.x() - lightPos.x();
            float distY = (world.y() - lightPos.y()) / TileBasics::TileAspectRatio;
            float inv = invSqrt(distX * distX + distY * distY);

            red   += (int)(light.red()   * light.getRange() * inv);
            green += (int)(light.green() * light.getRange() * inv);
            blue  += (int)(light.blue()  * light.getRange() * inv);
            fog   += (int)(light.fog()   * light.getRange() * inv);
        }
        dest = Color(red, green, blue, fog);
    }

    //------------------------------------------------------------------------------------------------------------
    Color LocationRenderer::modifyWithGamma(const Color & color) const
    {
        return Color(
            (unsigned char)((float)color.red()   * m_gamma),
            (unsigned char)((float)color.green() * m_gamma),
            (unsigned char)((float)color.green() * m_gamma),
            color.alpha());
    }
} // namespace Core4
