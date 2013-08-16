#include "Utils/Guards.hxx"
#include "Utils/StringUtils.hxx"
#include "Logging/LogHelpers.hxx"
#include "Render/win32/Direct3DVertexBuffer.hxx"

namespace Core4
{
    //------------------------------------------------------------------------------
    Direct3DVertexBuffer::Direct3DVertexBuffer() : m_fvf(0), m_vertexSize(0), m_vb(NULL)
    {
    }

    //------------------------------------------------------------------------------
    void Direct3DVertexBuffer::create(IDirect3DDevice9 * device, size_t numVertices, size_t vertexSize, DWORD fvf)
    {
        CORE4_CHECK(NULL == m_vb, "Vertex buffer already created");
        m_fvf = fvf;
        m_vertexSize = vertexSize;

        const size_t bufferSize = numVertices * vertexSize;

        CORE4_LOG_MESSAGE("Creating vertex buffer (" + StringUtils::intToString(bufferSize) + " bytes)");
        CORE4_CHECK(
            SUCCEEDED(
                device->CreateVertexBuffer(
                    bufferSize,
                    D3DUSAGE_DYNAMIC,
                    fvf,
                    D3DPOOL_DEFAULT,
                    &m_vb,
                    NULL)),
            "Could not create vertex buffer");
    }

    //------------------------------------------------------------------------------
    void Direct3DVertexBuffer::setStreamSource(IDirect3DDevice9 * device)
    {
         device->SetStreamSource(0, m_vb, 0, m_vertexSize);
         device->SetFVF(m_fvf);
    }

    //------------------------------------------------------------------------------
    bool Direct3DVertexBuffer::fill(const std::vector<char> & data)
    {
        char * dest(0);
        if (SUCCEEDED(m_vb->Lock(0, 0, (void**)&dest, D3DLOCK_DISCARD)))
        {
            memcpy(dest, &(data[0]), data.size());
            m_vb->Unlock();
            return true;
        }
        return false;
    }

    //------------------------------------------------------------------------------
    void Direct3DVertexBuffer::destroy()
    {
        SAFE_RELEASE(m_vb);
    }
} // namespace Core4

