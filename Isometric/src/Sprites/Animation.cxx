#include "Sprites/Animation.hxx"
#include "Sprites/SpriteManager.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    Animation::Animation() :
        m_maxTime(0),
        m_time(0),
        m_spriteIndex(0),
        m_startFrame(0),
        m_endFrame(0),
        m_currentFrame(m_startFrame),
        m_fps(0),
        m_loop(0),
        m_isPlaying(false),
        m_listener(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    Animation::Animation(size_t spriteIndex) :
        m_maxTime(0),
        m_time(0),
        m_spriteIndex(0),
        m_startFrame(0),
        m_endFrame(0),
        m_currentFrame(m_startFrame),
        m_fps(0),
        m_loop(0),
        m_isPlaying(false),
        m_listener(NULL)
    {
        setup(spriteIndex);
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::setup(size_t spriteIndex)
    {
        const Sprite & sprite = SpriteManager::getSingleton().getSprite(spriteIndex);
        m_spriteIndex  = spriteIndex;
        m_startFrame   = 0;
        m_endFrame     = sprite.getFrameCount() - 1;
        m_fps          = sprite.getFPS();
        m_maxTime      = 1000.f / m_fps;
        m_currentFrame = m_startFrame;
        m_isPlaying    = false;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::update(float dt)
    {
        if (!m_isPlaying)
            return;
        m_time += dt;
        if (m_time >= m_maxTime)
        {
            if (m_currentFrame < m_endFrame)
            {
                m_currentFrame++;
            }
            else
            {
                if (m_loop)
                {
                    m_currentFrame = m_startFrame;
                }
                else
                {
                    m_isPlaying = false;
                    if (NULL != m_listener)
                        m_listener->animationFinished();
                }
            }
            m_time = 0;
        }
    }

    //--------------------------------------------------------------------------------------------------------
    size_t Animation::getCurrentFrame() const
    {
        return m_currentFrame;
    }

    void Animation::setCurrentFrame(const size_t frame)
    {
        m_currentFrame = frame;
        if (m_currentFrame > m_endFrame)
            m_currentFrame = m_endFrame; // Frame index is too large
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::rewind()
    {
        m_currentFrame = 0;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::playWithListener(bool loop, Listener * listener)
    {
        m_listener  = listener;
        m_loop      = loop;
        m_isPlaying = true;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::play(bool loop)
    {
        playWithListener(loop, 0);
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::stop()
    {
        m_isPlaying = false;
        if (NULL != m_listener)
            m_listener->animationFinished();
    }

    //--------------------------------------------------------------------------------------------------------
    bool Animation::isPlaying() const
    {
        return m_isPlaying;
    }

    //--------------------------------------------------------------------------------------------------------
    bool Animation::isLooped() const
    {
        return m_loop;
    }

    //--------------------------------------------------------------------------------------------------------
    const size_t Animation::getSpriteIndex() const
    {
        return m_spriteIndex;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_maxTime);
        C4_SERIALIZE_ATTR(m_time);
        C4_SERIALIZE_ATTR(m_spriteIndex);
        C4_SERIALIZE_ATTR(m_startFrame);
        C4_SERIALIZE_ATTR(m_endFrame);
        C4_SERIALIZE_ATTR(m_currentFrame);
        C4_SERIALIZE_ATTR(m_fps);
        C4_SERIALIZE_ATTR(m_loop);
        C4_SERIALIZE_ATTR(m_isPlaying);
    }
} // namespace C4
