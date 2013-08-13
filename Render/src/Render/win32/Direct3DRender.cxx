#include <time.h>
#include "Render/win32/Direct3DCommon.hxx"
#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Logging/LogHelpers.hxx"
#include "Render/win32/Direct3DRender.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Direct3DRender::Direct3DRender(HWND hWnd) :
	    m_d3d(NULL),
	    m_device(NULL),
	    m_vb(NULL),
        m_maxAutoZ(1.f - 1.f / MaxSprites),
	    m_autoZ(m_maxAutoZ),
	    m_previousTime(0),
	    m_numFrames(0),
	    m_numSprites(0),
	    m_textureMemory(0),
        m_hWnd(hWnd)
    {
        ZeroMemory(&m_caps, sizeof(D3DCAPS9));
	    ZeroMemory(&m_presentParams, sizeof(D3DPRESENT_PARAMETERS));
    }

    //------------------------------------------------------------------------------
    Direct3DRender::~Direct3DRender()
    {
    }

    //------------------------------------------------------------------------------
    const std::string & Direct3DRender::getName() const
    {
        static const std::string name("Direct3D9");
        return name;
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::init(int width, int height, int bpp, bool windowed)
    {
	    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	    CORE4_CHECK(NULL != m_d3d, "Could not initialize Direct3D");

        // Get current desktop display mode
        D3DDISPLAYMODE displayMode;
        CORE4_CHECK(SUCCEEDED(m_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)), "Could not get display mode");

        ZeroMemory(&m_presentParams, sizeof(D3DPRESENT_PARAMETERS));
        if (windowed)
        {
            m_presentParams.Windowed               = TRUE;
            m_presentParams.SwapEffect             = D3DSWAPEFFECT_DISCARD;
            m_presentParams.BackBufferFormat       = displayMode.Format;
            m_presentParams.EnableAutoDepthStencil = TRUE;
            m_presentParams.AutoDepthStencilFormat = D3DFMT_D16;
        }
        else
        {
		    m_presentParams.Windowed               = FALSE;
  	        m_presentParams.hDeviceWindow          = m_hWnd;
  	        m_presentParams.SwapEffect             = D3DSWAPEFFECT_FLIP;
		    m_presentParams.BackBufferFormat       = displayMode.Format;
		    m_presentParams.EnableAutoDepthStencil = TRUE;
		    m_presentParams.AutoDepthStencilFormat = D3DFMT_D16;
		    m_presentParams.BackBufferWidth        = width;
		    m_presentParams.BackBufferHeight       = height;
		    m_presentParams.BackBufferCount            = 1;
		    m_presentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
            m_presentParams.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;
        }

        HRESULT res = m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            m_hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &m_presentParams,
            &m_device);

        CORE4_CHECK(D3DERR_NOTAVAILABLE != res, "This device does not support the queried technique");
        CORE4_CHECK(D3DERR_OUTOFVIDEOMEMORY != res, "Out of video memory");
        CORE4_CHECK(SUCCEEDED(res), "Could not create Direct3D device: invalid call");
        CORE4_CHECK(SUCCEEDED(m_device->GetDeviceCaps(&m_caps)), "Could not get Direct3D device caps");
        initDevice();
        m_stats = RenderStats();
        m_spriteVertices.resize(MaxVertices * sizeof(SpriteVertex));
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::cleanup()
    {
        CORE4_LOG_MESSAGE("Doing renderer cleanup");
        unloadAllTextures();
        destroyGeometry();
        SAFE_RELEASE(m_device);
        SAFE_RELEASE(m_d3d);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::clearScreen(const Color & color)
    {
        if (NULL != m_device)
        {
            m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                D3DCOLOR_RGBA(color.red(), color.green(), color.blue(), color.alpha()),
                1.0f,
                0);
        }
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::render()
    {
        if (NULL != m_device)
        {
            const size_t numSprites = m_spriteAttributes.size();
            size_t numTextures(0);

            m_autoZ = m_maxAutoZ;
            if (!m_spriteAttributes.empty())
            {
                // 1. Copy vertices into VB
                char * bytes(0);
                if (SUCCEEDED(m_vb->Lock(0, 0, (void**)&bytes, D3DLOCK_DISCARD)))
                {
                    memcpy(bytes, &(m_spriteVertices[0]), m_spriteVertices.size());
                    m_vb->Unlock();
                    if (SUCCEEDED(m_device->BeginScene()))
                    {
                        // 2. Draw all sprites.
                        SpriteAttributes prevAtts;
                        size_t baseVertex(0);
                        for (std::list<SpriteAttributes>::iterator it = m_spriteAttributes.begin(); it != m_spriteAttributes.end(); it++)
                        {
                            SpriteAttributes & atts = (*it);
                            // Switch texture if necessary
                            if (atts.texture != prevAtts.texture)
                            {
                                m_device->SetTexture(0, static_cast<IDirect3DTexture9*>(atts.texture->getInnerTexture()));
                                numTextures++;
                            }

                            // Do not switch render states until necessary
                            if (atts.useAlpha != prevAtts.useAlpha)
                            {
                                enableAlpha(atts.useAlpha);
                            }

                            m_device->DrawPrimitive(D3DPT_TRIANGLELIST, baseVertex, 2);

                            const size_t VerticesPerSprite = 6;
                            prevAtts = atts;
                            baseVertex += VerticesPerSprite;
                        } // for
                        m_device->EndScene();
                        m_spriteAttributes.clear();
                    } // if
                } // if
            } // if

            HRESULT res = m_device->Present(NULL, NULL, NULL, NULL);
            if (D3DERR_DEVICELOST == res)
            {
                CORE4_LOG_SECTION("Device is lost");
                // 1. Wait
                while (D3DERR_DEVICENOTRESET != m_device->TestCooperativeLevel())
                {
                    CORE4_LOG_INFO("Waiting...");
                    ::Sleep(1000);
                }
                // 2. Release all the D3DPOOL_DEFAULT stuff
                destroyGeometry();
                CORE4_LOG_INFO("Resetting lost device");
                // 3. Âevice reset
                CORE4_CHECK(SUCCEEDED(m_device->Reset(&m_presentParams)), "Could not reset Direct3D device");
                // 4. Recover lost resources.
                initDevice();
            }
            else
            {
                CORE4_CHECK(SUCCEEDED(res), "Could not present scene");
            }

            // Update FPS
            time_t currTime = time(0);
            if (currTime >= m_previousTime + 1)
            {
                m_stats.setFPS(m_numFrames);
                m_previousTime = currTime;
                m_numFrames = 0;
            }
            else
            {
                m_numFrames++;
            }

            m_stats.setNumSprites(numSprites);
            m_stats.setNumTextures(numTextures);
            m_stats.setTexturesMemory(m_textureMemory);
            m_numSprites = 0;
        }
    }

    //------------------------------------------------------------------------------
    const RenderStats & Direct3DRender::getStats() const
    {
        return m_stats;
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::enableAlpha(bool enable)
    {
        if (NULL != m_device)
        {
            if (m_caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL)
            {
                m_device->SetRenderState(D3DRS_ALPHATESTENABLE, enable ? TRUE : FALSE);
            }
            m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, enable ? TRUE : FALSE);
        }
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::drawSprite(float screenX, float screenY, const Sprite & sprite, ITexture * texture)
    {
        CORE4_CHECK(NULL != texture, "Texture is NULL");
	    float textureWidth  = static_cast<float>(texture->getWidth());
	    float textureHeight = static_cast<float>(texture->getHeight());

	    const float tu1 = (sprite.bitmapX) / textureWidth;
	    const float tv1 = (sprite.bitmapY) / textureHeight;
	    const float tu2 = (sprite.bitmapX + sprite.width) / textureWidth;
	    const float tv2 = (sprite.bitmapY + sprite.height) / textureHeight;

        // $TODO $FIX $HACK: sometimes there's a problem with texture mapping.
        screenX -= 0.5f;
        screenY -= 0.5f;

	    // Copy vertices
	    SpriteVertex quad[NumCorners] =
	    {
	        // x                      y                        z        rhw  d  s  u    v
	        { screenX,                screenY,                 m_autoZ, 1.f, 0, 0, tu1, tv1 },
	        { screenX,                screenY + sprite.height, m_autoZ, 1.f, 0, 0, tu1, tv2 },
	        { screenX + sprite.width, screenY,                 m_autoZ, 1.f, 0, 0, tu2, tv1 },
	        { screenX + sprite.width, screenY + sprite.height, m_autoZ, 1.f, 0, 0, tu2, tv2 }
	    };

	    for (size_t i = 0; i < NumCorners; i++)
	    {
	        const Color & d  = sprite.diffuse[i];
	        const Color & s  = sprite.specular[i];
	        quad[i].diffuse  = D3DCOLOR_RGBA(d.red(), d.green(), d.blue(), d.alpha());
	        quad[i].specular = D3DCOLOR_RGBA(s.red(), s.green(), s.blue(), s.alpha());
	    }
	    drawQuad(quad, texture, sprite.alpha);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::drawIsoTile(float screenX, float screenY, const Sprite & sprite, const float heights[NumCorners], ITexture * texture)
    {
        CORE4_CHECK(NULL != texture, "Texture is NULL");
	    float textureWidth  = static_cast<float>(texture->getWidth());
	    float textureHeight = static_cast<float>(texture->getHeight());

        const float texX = sprite.bitmapX / textureWidth;
        const float texY = sprite.bitmapY / textureHeight;
        const float texW = sprite.width   / textureWidth;
        const float texH = sprite.height  / textureHeight;

        const struct UV
        {
            float u, v;
        } coords[NumCorners] =
        {
            { texX + texW * .5f, texY },
            { texX,              texY + texH * .5f },
            { texX + texW,       texY + texH * .5f },
            { texX + texW * .5f, texY + texH }
        };

	    // Copy vertices
	    SpriteVertex quad[NumCorners] =
	    {
	        // x                                   y                       z        rhw  d  s
	        { screenX + sprite.width / 2.f, screenY,                       m_autoZ, 1.f, 0, 0 },
	        { screenX,                      screenY + sprite.height / 2.f, m_autoZ, 1.f, 0, 0 },
	        { screenX + sprite.width,       screenY + sprite.height / 2.f, m_autoZ, 1.f, 0, 0 },
	        { screenX + sprite.width / 2.f, screenY + sprite.height,       m_autoZ, 1.f, 0, 0 }
	    };

	    for (size_t i = 0; i < NumCorners; i++)
	    {
	        const Color & d  = sprite.diffuse[i];
	        const Color & s  = sprite.specular[i];
	        quad[i].diffuse  = D3DCOLOR_RGBA(d.red(), d.green(), d.blue(), d.alpha());
	        quad[i].specular = D3DCOLOR_RGBA(s.red(), s.green(), s.blue(), s.alpha());
	        quad[i].y       -= heights[i];
	        quad[i].u        = coords[i].u;
	        quad[i].v        = coords[i].v;
	    }
	    drawQuad(quad, texture, sprite.alpha);
    }

    //------------------------------------------------------------------------------
    ITexture * Direct3DRender::getTexture(const std::string & filename, IImageLoader * loader)
    {
        Textures::const_iterator it = m_textures.find(filename);
        if (it != m_textures.end()) 
        {
            return it->second;
        }
        else
        {
            Direct3DTexture * texture = new Direct3DTexture();
	        texture->create(m_device, loader, filename);

            const size_t kb = texture->getSizeKB();
	        m_textureMemory += kb;

            CORE4_LOG_MESSAGE(
                "Texture loaded: \"" + 
                filename + 
                "\" (" + 
                StringUtils::intToString(texture->getWidth()) +
                "x" + 
                StringUtils::intToString(texture->getHeight()) +
                "), " +
                StringUtils::intToString(kb) +
                "KB");
            m_textures[filename] = texture;
		    return texture;
        }
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::unloadTexture(ITexture * texture)
    {
          CORE4_CHECK(NULL != texture, "Texture is NULL");
          const std::string & name = texture->getName();
          Textures::iterator it = m_textures.find(name);
          CORE4_CHECK(it != m_textures.end(), "No such texture: \"" + name + "\"");

          int memoryKB = m_stats.getTexturesMemory() - it->second->getSizeKB(); 
          delete it->second; 
          m_textures.erase(it);
          m_stats.setTexturesMemory(memoryKB);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::unloadAllTextures()
    {
        for (Textures::iterator it = m_textures.begin(); it != m_textures.end(); it++)
        {
            delete it->second;
        }
        m_textures.clear();
        m_stats.setTexturesMemory(0);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::drawQuad(const SpriteVertex vertices[NumCorners], ITexture * texture, bool alpha)
    {
        // Turn 4 vertices into 6
        const size_t spriteCount = m_spriteAttributes.size();
        CORE4_CHECK(MaxSprites > spriteCount, "Too many sprites");
	    CORE4_CHECK(NULL != texture, "Texture is NULL");

        const size_t VerticesPerSprite = 6;
        size_t indices[VerticesPerSprite] = { 2, 1, 0, 1, 2, 3 };
        for (size_t i = 0; i < VerticesPerSprite; i++)
        {
            const size_t & index        = indices[i];
            const SpriteVertex & vertex = vertices[index];
            const size_t offset         = ((spriteCount * 6) + i) * sizeof(SpriteVertex);
            memcpy(&m_spriteVertices[offset], &vertex, sizeof(SpriteVertex));
        }
        m_spriteAttributes.push_back(SpriteAttributes(texture, alpha));
        m_autoZ -= (1.f / MaxSprites);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::setRenderStates()
    {
        CORE4_LOG_MESSAGE("Setting up render & samples states");

        m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        m_device->SetRenderState(D3DRS_LIGHTING, FALSE);

    /*
        m_device->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
        m_device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
        m_device->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
    */
        m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
        m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

        m_device->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 255, 255));
        m_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
        m_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

        m_device->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

        if (m_caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL)
        {
            m_device->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
            m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
        }
        m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
     }

    //------------------------------------------------------------------------------
    void Direct3DRender::createGeometry()
    {
        CORE4_CHECK(NULL == m_vb, "Vertex buffer already created");

        CORE4_LOG_MESSAGE("Creating vertex buffer");

        CORE4_CHECK(
            SUCCEEDED(
                m_device->CreateVertexBuffer(
                    MaxVertices * sizeof(SpriteVertex),
                    D3DUSAGE_DYNAMIC,
                    SpriteFVF,
                    D3DPOOL_DEFAULT,
                    &m_vb,
                    NULL)),
            "Could not create vertex buffer");

        m_device->SetStreamSource(0, m_vb, 0, sizeof(SpriteVertex));
        m_device->SetFVF(SpriteFVF);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::destroyGeometry()
    {
        SAFE_RELEASE(m_vb);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::initDevice()
    {
        createGeometry();
        setRenderStates();
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::specularEnable(bool enable)
    {
        m_device->SetRenderState(D3DRS_SPECULARENABLE, enable ? TRUE : FALSE);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::fogEnable(bool enable)
    {
        m_device->SetRenderState(D3DRS_FOGENABLE, enable ? TRUE : FALSE);
    }

    //------------------------------------------------------------------------------
    void Direct3DRender::setFogColor(const Color & color)
    {
        m_device->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_RGBA(color.red(), color.green(), color.blue(), color.alpha()));
    }
} // namespace Core4
