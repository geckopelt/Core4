#pragma once

/// @file Direct3DRender.hxx
/// @brief Direct3D Render Implementation
#include "Render/IRenderSystem.hxx"
#include "Render/win32/Direct3DCommon.hxx"
#include "Render/win32/Direct3DTexture.hxx"
#include "Render/win32/Direct3DVertexBuffer.hxx"

namespace Core4
{
    /// Direct3D render implementation.
    class Direct3DRender : public IRenderSystem
    {
    public:
        /// Ctor.
        /// @param Parent HWND to use
	    Direct3DRender(HWND hWnd);

        /// Dtor.
	    virtual ~Direct3DRender();

        /// @see IRenderSystem
    	void init(int width, int height, int bpp, bool windowed);

        /// @see IRenderSystem
	    void render();

        /// @see IRenderSystem
	    const RenderStats & getStats() const;

        /// @see IRenderSystem
 	    const std::string & getName() const;

        /// @see IRenderSystem
	    void cleanup();

        /// @see IRenderSystem
	    void clearScreen(const Color & color);

        /// @see IRenderSystem
	    void drawSprite(float screenX, float screenY, const Sprite & sprite, ITexture * texture);

        /// @see IRenderSystem
	    void drawIsoTile(float screenX, float screenY, const Sprite & sprite, const float heights[NumCorners], ITexture * texture);

        /// @see IRenderSystem
        void drawLine(const PrimitivePoint & start, const PrimitivePoint & end);

        /// @see IRenderSystem
	    void specularEnable(bool enable);

        /// @see IRenderSystem
	    void fogEnable(bool enable);
	    
        /// @see IRenderSystem
        void setFogColor(const Color & color);

        /// @see IRenderSystem
        ITexture * getTexture(const std::string & filename, IImageLoader * loader);

        /// @see IRenderSystem
        void unloadTexture(ITexture * texture);

	    /// @see IRenderSystem
	    void unloadAllTextures();
    private:
        Direct3DRender(const Direct3DRender &);

        void renderSprites();
        void renderPrimitives();

        struct SpriteVertex
        {
            float x, y, z, rhw;
            DWORD diffuse;
            DWORD specular;
            float u, v;
        };

        struct PrimitiveVertex
        {
            float x, y, z, rhw;
            DWORD diffuse;
        };

        struct SpriteAttributes
        {
            ITexture * texture;
            bool       useAlpha;

            SpriteAttributes() : texture(0), useAlpha(false) {}
            SpriteAttributes(ITexture * t, bool a) : texture(t), useAlpha(a) {}
        };

        std::list<SpriteAttributes> m_spriteAttributes;  //< Sprite attributes.
        std::vector<char>           m_spriteVertices;    //< Sprite vertices.
        std::vector<char>           m_primitiveVertices; //< Primitive vertices. 

	    void setRenderStates();
	    void createGeometry();
	    void destroyGeometry();
	    void initDevice();
	    void enableAlpha(bool enable);

	    void drawQuad(const SpriteVertex vertices[NumCorners], ITexture * texture, bool alpha);

        static const DWORD SpriteFVF    = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1;
        static const DWORD PrimitiveFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

        static const size_t MaxSprites           = 8192;
        static const size_t MaxVertices          = MaxSprites * 6;
        static const size_t MaxPrimitiveLines    = 8192;
        static const size_t MaxPrimitiveVertices = MaxPrimitiveLines * 2;

        time_t                   m_previousTime;  //< For FPS calculation purposes
        size_t                   m_numFrames;     //< For FPS calculation purposes
        size_t                   m_numSprites;    //< Number of sprites currently visible
        size_t                   m_numLines;      //< Number of lines currently visible
        size_t                   m_textureMemory; //< Texture memory (in KB)
        float                    m_maxAutoZ;      //< Auto Z assignment thingy
        float                    m_autoZ;         //< Ditto
        IDirect3D9 *             m_d3d;           //< D3D interface
        IDirect3DDevice9 *       m_device;        //< D3D device interface
        Direct3DVertexBuffer     m_spriteVB;      //< VB for sprites
        Direct3DVertexBuffer     m_primitiveVB;   //< VB for primitives
        RenderStats              m_stats;         //< Render stats
        D3DCAPS9                 m_caps;          //< Device capabilities
        D3DPRESENT_PARAMETERS    m_presentParams; //< Device present params
        HWND                     m_hWnd;          //< Parent window

        typedef std::map<std::string, ITexture*> Textures;
        Textures                 m_textures;      //< Loaded textures
    };
} // namespace Core4

