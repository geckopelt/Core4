#pragma once

/// @file Direct3DVertexBuffer.hxx
/// @brief Direct3D vertex buffer wrapper

#include "Image/IImageLoader.hxx"
#include "Render/ITexture.hxx"
#include "Render/win32/Direct3DCommon.hxx"

namespace Core4
{
    /// Direct3D vertex buffer wrapper.
    class Direct3DVertexBuffer
    {
    public:
        /// Ctor.
        Direct3DVertexBuffer();

        /// Create a vertex buffer.
        /// @param device Parent device.
        /// @param numVertices Number of vertices.
        /// @param vertexSize Single vertex size.
        /// @aram fvf Vertex format.
        void create(IDirect3DDevice9 * device, size_t numVertices, size_t vertexSize, DWORD fvf);

        /// Set this VB as a source.
        /// @param device Parent device.
        void setStreamSource(IDirect3DDevice9 * device);

        /// Fill this VB.
        /// @param data Vertex data to fill in.
        /// @return true if succeeded.
        bool fill(const std::vector<char> & data);

        /// Destroy a vertex buffer.
        void destroy();
    private:
        DWORD                    m_fvf;
        size_t                   m_vertexSize;
        IDirect3DVertexBuffer9 * m_vb;
    };
} // namespace Core4
