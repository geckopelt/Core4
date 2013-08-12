#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Render/win32/Direct3DTexture.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Direct3DTexture::Direct3DTexture() : 
        m_texture(0),
        m_width(0),
        m_height(0),
        m_sizeKB(0),
        m_locked(false)
    {
        ZeroMemory(&m_lockedRect, sizeof(D3DLOCKED_RECT));
    }

    //------------------------------------------------------------------------------
    Direct3DTexture::~Direct3DTexture()
    {
        destroy();
    }

    //------------------------------------------------------------------------------
    void Direct3DTexture::create(
        IDirect3DDevice9 * device,
  		IImageLoader * loader,
        const std::string & name)
    {
        CORE4_CHECK(NULL != loader, "Could not load texture \"" + name + "\", because loader is NULL");
        destroy();

        const std::vector<unsigned char> bitmap = loader->loadTexture(name, m_width, m_height);

        const int Levels = 1;

        CORE4_CHECK(
            SUCCEEDED(
                device->CreateTexture(
                    m_width,
                    m_height,
                    Levels,
                    0,
                    D3DFMT_A8R8G8B8,
                    D3DPOOL_MANAGED,
                    &m_texture,
                    NULL)),
            "Could not create texture for \"" + name + "\"");

        lock();
        const size_t RowWidth = m_width * 4;
        unsigned char * bits = (unsigned char*)m_lockedRect.pBits;
        unsigned char * data = (unsigned char*)&bitmap[0];
        for (size_t y = 0; y < m_height; y++)
        {
            memcpy(bits, data, RowWidth);
            bits += m_lockedRect.Pitch;
            data += RowWidth;
        }
        unlock();

        m_name   = name;
        m_sizeKB = bitmap.size() / 1024;
    }

    //------------------------------------------------------------------------------
    void Direct3DTexture::destroy()
    {
        SAFE_RELEASE(m_texture);
	    m_name.clear();
	    m_width = m_height = m_sizeKB = 0;
    }

    //------------------------------------------------------------------------------
    const std::string & Direct3DTexture::getName() const
    {
        return m_name;
    }

    //------------------------------------------------------------------------------
    const size_t Direct3DTexture::getWidth() const
    {
        return m_width;
    }

    //------------------------------------------------------------------------------
    const size_t Direct3DTexture::getHeight() const
    {
        return m_height;
    }

    //------------------------------------------------------------------------------
    void Direct3DTexture::lock()
    {
        CORE4_CHECK(!m_locked, "Texture already locked: \"" + m_name + "\"");
        CORE4_CHECK(SUCCEEDED(m_texture->LockRect(0, &m_lockedRect, NULL, 0)),
            "Could not lock texture rect for \"" + m_name + "\"");
        m_locked = true;
    }

    //------------------------------------------------------------------------------
    Color Direct3DTexture::getPixel(size_t x, size_t y)
    {
        CORE4_CHECK(m_locked, "Texture is not locked: \"" + m_name + "\"");
        CORE4_CHECK(x < m_width && y < m_height, 
            "Invalid texture coordinates: (" + 
            StringUtils::intToString(x) +
            ", " + 
            StringUtils::intToString(y) + 
            " (" + m_name + ")");

        const size_t offset = y * m_lockedRect.Pitch + x * 4;
        char * bits = (char*)m_lockedRect.pBits + offset;

        const int RedIndex = 2;
        const int GreenIndex = 1;
        const int BlueIndex = 0;
        const int AlphaIndex = 3;

        return Color(bits[RedIndex], bits[GreenIndex], bits[BlueIndex], bits[AlphaIndex]); 
    }

    //------------------------------------------------------------------------------
    void Direct3DTexture::unlock()
    {
        CORE4_CHECK(m_locked, "Texture is not locked: \"" + m_name + "\"");
        m_texture->UnlockRect(0);
        m_locked = false;
    }

    //------------------------------------------------------------------------------
    const size_t Direct3DTexture::getSizeKB() const
    {
        return m_sizeKB;
    }

    //------------------------------------------------------------------------------
    void * Direct3DTexture::getInnerTexture()
    {
        return (void*)m_texture;
    }
} // namespace Core4