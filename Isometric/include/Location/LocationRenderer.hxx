#pragma once

/// @file LocationRenderer.hxx
/// @brief Isometric location renderer

#include "Utils/Singleton.hxx"
#include "Types/Rect.hxx"
#include "Common/IUpdateable.hxx"
#include "Render/IRenderSystem.hxx"
#include "Sprites/Sprite.hxx"
#include "Location/LocationMap.hxx"
#include "Location/BoundingBox.hxx"
#include "Debug/IDebugRenderer.hxx"

namespace Core4
{
    /// Isometric location renderer.
    class LocationRenderer : 
        public Singleton<LocationRenderer>
    {
    public:
        /// Ctor.
        LocationRenderer();

        /// Dtor.
        virtual ~LocationRenderer();

        /// Initialize locaion renderer.
        /// @param renderSystem Render system to use.
        /// @param screenSize Screen size to use.
        void init(IRenderSystem * renderSystem, const Vector2 & screenSize);

        /// Draw the map.
        void render();

        /// Set current location map.
        /// @param locationMap Location map pointer.
        void setLocationMap(LocationMap * locationMap);

        /// Get current location map
        /// @return Location map pointer.
        const LocationMap * getLocationMap() const;

        /// Get current scroll position.
        /// @return Current scroll position, in pixels.
        const Vector2 & getScrollPos() const;

        /// Set current scroll position.
        /// @param pos Scroll position, in pixels.
        void setScrollPos(const Vector2 & pos);

        /// Convert screen coordinates into map coordinates.
        /// @param Screen point, in pixels.
        /// @return Map point, in pixels.
        const Vector2 screenToWorld(const Vector2 & screen);

        /// Convert map coordinates into screen coordinates.
        /// @param Map point, in pixels.
        /// @return Screen point, in pixels.
        const Vector2 worldToScreen(const Vector2 & world);

        /// Set visible map screen size.
        /// @param size Screen size, in pixels.
        void setScreenSize(const Vector2 & size);
        
        /// Get visible map screen size.
        /// @return Screen size, in pixels
        const Vector2 & getScreenSize() const;

        /// Get current scroll rect.
        /// @return Scroll rect.
        const Rect getScrollRect() const;
        
        /// Whether to show blocked tiles (debug rendering).
        /// @param Yes/No.
        void showBlockedTiles(bool show);

        /// Are blocked tiles shown?
        /// @return Yes/No
        bool blockedTilesShown() const;

        /// Render a sprite.
        /// @param screenPos Sprite coordinates, in pixels.
        /// @param sprite Sprite details.
        /// @param frame Sprite frame number.
        void renderSprite(const Vector2 & screenPos, const Sprite & sprite, const size_t frame) const;

        /// Get object at given screen position. Useful for mouse selection.
        /// @param screen Screen position in pixeld.
        /// @return Object pointer or NULL if not found.
        LocationMapObject * getObjectAtPos(const Vector2 & screen);

        /// Get current background color.
        /// @return Background color.
        const Color & getBackgroundColor() const;
        
        /// Set current background color.
        /// @param color Background color.
        void setBackgroundColor(const Color & color);

        /// Clear screen with appropriate gamma-corrected background color.
        void clearScreen();

        /// Enable or disable fog.
        /// @param enable Enable/disable.
        void enableFog(bool enable);

        /// Is fog enabled?
        /// @return Yes/No
        bool isFogEnabled() const;

        /// Set fog color.
        /// @param color Fog color.
        void setFogColor(const Color & color);

        /// Get fog color.
        /// @param Fog color.
        const Color & getFogColor() const;

        /// Set fog density.
        /// @param density Fog density (0..1)
        void setFogDensity(float density);

        /// Get current fog density.
        /// @return Current fog density.
        float getFogDensity() const;
        
        /// Set gamma.
        /// @param gamma Gamma (0..1)
        void setGamma(float gamma);
        
        /// Get current gamma.
        /// @return Gamma value.
        float getGamma() const;
    private:
        void calcLightsAtPoint(const Vector2 & world, Color & dest ) const;
        Color modifyWithGamma(const Color & color) const;

        IRenderSystem *        m_renderSystem;
        LocationMap *          m_locationMap;
        Rect                   m_screenSpace;
        Rect                   m_worldRect;
        Vector2                m_screenAnchor;
        std::list<BoundingBox> m_objectBounds;
        bool                   m_showBlockedTiles;
        Color                  m_backgroundColor;
        Color                  m_fogColor;
        float                  m_fogDensity;
        bool                   m_fogEnabled;
        float                  m_gamma;
        std::vector<Color>     m_approxCellLighting;
        IDebugRenderer *       m_debugRenderer;
    };
} // namespace Core4
