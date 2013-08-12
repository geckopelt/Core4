#pragma once

/// @file RenderStats.hxx
/// @brief Render statistics container

namespace Core4
{
    /// Core4 render stats
    class RenderStats
	{
    public:
        /// Default ctor. Initializes all the values.
        RenderStats();

        /// Set number of visible sprites.
        /// @param numSprites Number of sprites.
        void setNumSprites(const size_t numSprites);

        /// Get number of visible sprites.
        /// @return Number of visible sprites.
        size_t getNumSprites() const;

        /// Set texture count.
        /// @param numTextures Number of textures totally used.
        void setNumTextures(const size_t numTextures);

        /// Get current texture count.
        /// @return Texture count.
        size_t getNumTextures() const;

        /// Set current FPS.
        /// @param fps Current FPS.
        void setFPS(size_t fps);

        /// Get current FPS.
        /// @return Current FPS.
        size_t getFPS() const;

        /// Set current textures memory consumption.
        /// @param texturesMemory Textures memory consumption, in KB.
        void setTexturesMemory(size_t texturesMemory);

        /// Get current textures memory consumption.
        /// @return Textures memory consumption, in KB.
        size_t getTexturesMemory() const;
    private:
	    size_t m_numSprites;
	    size_t m_numTextures;
	    size_t m_fps;
        size_t m_texturesMemory;
	};
} // namespace Core4