#include "Utils/Guards.hxx"
#include "Sprites/Animation.hxx"
#include "Sprites/SpriteManager.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------
    Animation::Animation() :
        m_maxTime(0),
        m_time(0),
        m_currentFrame(0),
        m_fps(0),
        m_loop(0),
        m_isPlaying(false),
        m_listener(NULL),
        m_spriteKey(0)
    {
    }

    //--------------------------------------------------------------------------------------------------------
    Animation::Animation(const ISpriteManager::SpriteKey & spriteKey) :
        m_maxTime(0),
        m_time(0),
        m_currentFrame(0),
        m_fps(0),
        m_loop(0),
        m_isPlaying(false),
        m_listener(NULL),
        m_spriteKey(0)
    {
        setup(spriteKey);
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::setup(const ISpriteManager::SpriteKey & spriteKey)
    {
        const Sprite & sprite = SpriteManager::getSingleton().getSprite(spriteKey);
        m_fps          = sprite.getFPS();
        m_maxTime      = 1000.f / m_fps;
        m_currentFrame = 0;
        m_isPlaying    = false;
        m_spriteKey    = spriteKey;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::update(float dt)
    {
        const Sprite & sprite = SpriteManager::getSingleton().getSprite(m_spriteKey);

        if (!m_isPlaying)
            return;
        m_time += dt;
        if (m_time >= m_maxTime)
        {
            if (m_currentFrame < sprite.getFrameCount() - 1)
            {
                m_currentFrame++;
            }
            else
            {
                if (m_loop)
                {
                    m_currentFrame = 0;
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

    //--------------------------------------------------------------------------------------------------------
    ISpriteManager::SpriteKey Animation::getSpriteKey() const
    {
        return m_spriteKey;
    }

    //--------------------------------------------------------------------------------------------------------
    void Animation::setCurrentFrame(const size_t frame)
    {
        const Sprite & sprite = SpriteManager::getSingleton().getSprite(m_spriteKey);
        CORE4_CHECK(frame < sprite.getFrameCount(), "Animation frame index too large");
        m_currentFrame = frame;
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
    void Animation::perform(TiXmlElement & element, const SerializeActionType action)
    {
        C4_SERIALIZE_ATTR(m_maxTime);
        C4_SERIALIZE_ATTR(m_time);
        C4_SERIALIZE_ATTR(m_spriteKey);
        C4_SERIALIZE_ATTR(m_currentFrame);
        C4_SERIALIZE_ATTR(m_fps);
        C4_SERIALIZE_ATTR(m_loop);
        C4_SERIALIZE_ATTR(m_isPlaying);
    }
} // namespace C4
