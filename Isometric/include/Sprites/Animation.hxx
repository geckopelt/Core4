#pragma once

/// @file Animation.hxx
/// @brief Sprite animation class.

#include <TinyXML.h>
#include "Serialization/Serializeable.hxx"
#include "Sprites/ISpriteManager.hxx"
#include "Common/IUpdateable.hxx"
#include <vector>

namespace Core4
{
    /// Sprite animation class.
    class Animation : public IUpdateable, public Serializeable
    {
    public:
        /// Animation listener callbacks.
        struct Listener
        {
            /// Called when animation sequence is finished.
            virtual void animationFinished() = 0;

            /// Dtor.
            virtual ~Listener() {}
        };

        /// Ctor. Initializes everything.
        Animation();

        /// Ctor.
        /// @see setup().
        Animation(const ISpriteManager::SpriteKey & spriteKey);

        /// @param spriteKeys Animation frames.
        void setup(const ISpriteManager::SpriteKey & spriteKey);

        /// @see IUpdateable.
        void update(float dt);

        /// Get current animation frame.
        /// @return Current animation frame number.
        size_t getCurrentFrame() const;

        /// Get current sprite key.
        /// @return Sprite key.
        ISpriteManager::SpriteKey getSpriteKey() const;

        /// Set current animation frame.
        /// @param frame Current animation frame number.
        void setCurrentFrame(const size_t frame);

        /// Reset animation to its first frame.
        void rewind();

        /// Start playback.
        /// @param loop Loop it?
        /// @param listener if not NULL, IListener::animationFinished() will be called when done.
        void playWithListener(bool loop, Listener * listener);

        // @see playWithListener().
        void play(bool loop);

        /// Stop animation playbacl.
        /// IListener::animationFinished() will be called, if specified..
        void stop();

        /// Is it playing?
        /// @return Yes/No.
        bool isPlaying() const;

        /// Is it looped?
        /// @return Yes/No.
        bool isLooped() const;

        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        float                     m_maxTime;
        float                     m_time;
        size_t                    m_currentFrame;
        size_t                    m_fps;
        bool                      m_loop;
        bool                      m_isPlaying;
        Listener *                m_listener;
        ISpriteManager::SpriteKey m_spriteKey;
    };
} // namespace Core4
