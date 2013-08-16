#pragma once

/// @file IRenderSystem.hxx
/// @brief 2D Render system interface

#include <string>
#include "Types/Color.hxx"
#include "Image/IImageLoader.hxx"
#include "Render/RenderStats.hxx"
#include "Render/ITexture.hxx"

namespace Core4
{
    /// A simple 2D render system interface.
    struct IRenderSystem
    {
        static const int NumCorners = 4;

        /// A sprite to render.
	    struct Sprite
	    {
            Sprite() : bitmapX(0), bitmapY(0), width(0), height(0), alpha(false) {}
            float bitmapX;     //< Bitmap X coord, in pixels.
            float bitmapY;     //< Bitmap Y coord, in pixels.
            float width;       //< Sprite width, in pixels.
            float height;      //< Sprite height, in pixels.
            Color diffuse[NumCorners];  //< Sprite corner colors (diffuse).
		    Color specular[NumCorners]; //< Sprite corner colors (specular).
		    bool  alpha;       //< Whether to use the alpha channel.
        };

        /// A primitive point
        struct PrimitivePoint
        {
            PrimitivePoint() : x(0), y(0) {}
            float x;     //< X coord, in pixels
            float y;     //< Y coord, in pixels
            Color color; //< Point color
        };

        /// Get render name.
        /// @return Render name.
        virtual const std::string & getName() const = 0;

        /// Initialize this render.
	    /// @param width Screen width, in pixels.
	    /// @param height Screen height, in pixels.
	    /// @param bpp Color depth, bits per pixel.
	    /// @param windowed Windowed or full screen mode
	    virtual void init(int width,
		                int height,
		                int bpp,
		                bool windowed) = 0;

        /// Cleanup everything.
	    virtual void cleanup() = 0;

        /// Clear screen.
        /// @param color Color to fill screen with.
	    virtual void clearScreen(const Color & color) = 0;

	    /// Render everything.
	    virtual void render() = 0;

	    /// Get render stats.
	    /// @return Current render statistics information.
	    virtual const RenderStats & getStats() const = 0;

        /// Draw a sprite.
        /// The sprite will be shown on next render() call.
        /// @param screenX X coord in pixels (left).
        /// @param screenY Y coord in pixels (top).
        /// @param sprite Sprite info.
        /// @param texture Sprite texture.
	    virtual void drawSprite(float screenX, float screenY, const Sprite & sprite, ITexture * texture) = 0;

        /// Draw an isometric tile.
        /// The tile will be shown on next render() call.
        /// Sprite::width and Sprite::height are tile's bounding box width and height.
        /// @param screenX X coord in pixels (left).
        /// @param screenY Y coord in pixels (top).
        /// @param sprite Sprite info..
        /// @param heights Pseudo-3D heights of a tile.
        /// @param texture Tile texture.
	    virtual void drawIsoTile(float screenX, float screenY, const Sprite & sprite, const float heights[NumCorners], ITexture * texture) = 0;

        /// Draw a line between two points.
        /// @param start Point 1
        /// @param start Point 2
        virtual void drawLine(const PrimitivePoint & start, const PrimitivePoint & end) = 0;

        /// Enable or disable specular color.
	    /// @param enable wat?.
	    virtual void specularEnable(bool enable) = 0;

        /// Enable or disable fog.
	    /// @param enable Enable fog?.
	    virtual void fogEnable(bool enable) = 0;

	    /// Set fog color.
	    /// @param color Fog color.
	    virtual void setFogColor(const Color & color) = 0;

        /// Get a texture pointer.
        /// Loads a texture if not loaded..
        /// @param name Texture filename.
        /// @param loader Loader to use.
        /// @return Texture pointer.
	    virtual ITexture * getTexture(const std::string & filename, IImageLoader * loader) = 0;

	    /// Unload a texture.
	    /// @param texture Texture pointer.
	    virtual void unloadTexture(ITexture * texture) = 0;

	    /// Unloads all textures.
	    virtual void unloadAllTextures() = 0;
       
	    virtual ~IRenderSystem() {}
    };
} // namespace Core4
