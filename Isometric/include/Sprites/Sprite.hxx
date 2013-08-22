#pragma once

#include <vector>
#include <string>
#include "Sprites/SpriteFrame.hxx"

/// @file Sprite.hxx
/// @brief A simple sprite implementation.

namespace Core4
{
    /// Sprite.
    /// A sprite consists of one or more frames, and can be animated with Animation class.
    class Sprite
    {
    public:
        /// Ctor.
        Sprite();

        /// Get sprite frame reference.
        /// @param index Frame number.
        /// @return Sprite frame reference.
        const SpriteFrame & getFrame(size_t index) const;

        /// Get sprite frame count.
        /// @return Sprite frame count.
        const size_t getFrameCount() const;

        /// Get sprite animation speed, in frames per second (for animated sprites only).
        /// @return Frames per second.
        const size_t getFPS() const;

        /// Check if alpha blending is enabled.
        /// @return True if enabled.
        const bool isAlphaEnabled() const;

        /// Add sprite frame.
        /// @param frame Sprite frame info.
        void addFrame(const SpriteFrame & frame);

        /// Set sprite's texture name.
        void setTextureName(const std::string & textureName);

        /// Enable or disable alpha blending.
        /// @param alpha On/Off.
        void setAlphaEnabled(bool alpha);

        /// Set animation speed (for animated sprites only).
        /// @param fps Animation speed, in frames per second.
        void setFPS(const size_t fps);

        /// Get sprite's texture name.
        /// @return Texture name.
        const std::string & getTextureName() const;

        /// Does this sprite have a texture?
        /// @return Yes/No.
        bool hasTexture() const;
    protected:
        friend class SpriteManager;
        friend class LocationRenderer;

        ITexture * getTexture() const;
        void setTexture(ITexture * texture);
    private:
        typedef std::vector<SpriteFrame> FrameList;
        std::string                      m_textureName;
        size_t                           m_fps;
        bool                             m_alphaEnabled;
        FrameList                        m_frames;
        std::string                      m_category;
        ITexture *                       m_texture;
    };
} // namespace Core4
