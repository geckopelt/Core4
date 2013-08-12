#pragma once

/// @file Direct3DTexture.hxx
/// @brief Direct3D texture implementation

#include "Image/IImageLoader.hxx"
#include "Render/ITexture.hxx"
#include "Render/win32/Direct3DCommon.hxx"

namespace Core4
{
    /// Direct3D texture wrapper
    class Direct3DTexture : public ITexture
    {    
    public:
        /// Ctor.
        Direct3DTexture();

        /// Dtor.
        virtual ~Direct3DTexture();

        /// @see ITexture
	    const std::string & getName() const;
	    
        /// @see ITexture
        const size_t getWidth() const;
	    
        /// @see ITexture
        const size_t getHeight() const;

        /// @see ITexture
        void lock();
        
        /// @see ITexture
	    Color getPixel(size_t x, size_t y);
	    
        /// @see ITexture
        void unlock();

        /// @see ITexture
        const size_t getSizeKB() const;

        /// @see ITexture
        void * getInnerTexture();

        /// Create a texture.
        /// @param device Parent device.
        /// @param loader Texture loader.
        /// @param name Texture name.
        void create(IDirect3DDevice9 * device, IImageLoader * loader, const std::string & name);

        /// Destroys a texture.
	    void destroy();
    private:
        bool                m_locked;
        size_t			    m_width;
        size_t              m_height;
        size_t              m_sizeKB;
        IDirect3DTexture9 * m_texture;
        std::string         m_name;
        D3DLOCKED_RECT      m_lockedRect;
    };
} // namespace Core4
