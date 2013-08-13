/* TODO

#include "C4Object.hxx"
#include "C4AppearanceManager.hxx"
#include "C4Render.hxx"
#include "C4Engine.hxx"

namespace C4
{

Object::Object() :
  m_temporary(false),
  m_layer(0),
  m_moveLerp(0.f),
  m_direction(UnknownDirection),
  m_destination(UnknownDirection),
  m_velocity(.0f),
  m_visible(false),
  m_blocksMovement(false),
  m_selectionEnabled(true)
{
  m_direction = UnknownDirection;
  m_color     = TRS::Color(0, 0, 0, 0);
}

Object::~Object()
{
}

int Object::getDirection() const
{
  return m_direction;
}

void Object::setWorldPos(const Point & pos)
{
  m_worldPos = pos;
}

void Object::update(float dt)
{
  m_animation.update(dt);

  if (UnknownDirection != m_destination)
  {
    const float deltaMoveLerp = (dt / ( (0 != m_direction %2) ? 500.0f : 1000.0f) ) * m_velocity;

    if (m_moveLerp < 1.f)
      m_moveLerp += deltaMoveLerp;
    else
    {
	    if (m_destination != SouthWest &&
	        m_destination != SouthEast &&
	        m_destination != East &&
	        m_destination != South)
			{
			  setWorldPos(Render::getSingleton().tileWalker(m_worldPos, m_destination));
			}
			m_startVector = Vector2(0.f, 0.f);
			m_endVector   = Vector2(0.f, 0.f);
      m_destination = UnknownDirection; // Прекратили двигаться.

      if (m_path.empty())
      {
        // OK, пришли.
        Engine::getSingleton().objectCallback(m_endCallback, (*this));
      }
      else
      {
        // Идем дальше.
        m_path.pop_back();

        if (!m_path.empty())
        {
          moveTo(m_path.at(m_path.size() - 1), m_velocity, m_endCallback);
        }
        else
        {
          Engine::getSingleton().objectCallback(m_endCallback, (*this));
        }
      }
    }
  }
}

void Object::moveTo(const int direction, float velocity, const std::string & endCallback)
{
  if (UnknownDirection != m_destination)
    return; // $TODO already moving

  m_endCallback = endCallback;

  m_destination = direction;
  m_moveLerp    = 0.f;
  m_velocity    = velocity;

  Render & render = Render::getSingleton();

  m_startVector = render.tilePlotter(m_worldPos);
  Point dest    = render.tileWalker(m_worldPos, m_destination);
  m_endVector   = render.tilePlotter(dest);

  if (m_destination == SouthWest ||
      m_destination == SouthEast ||
      m_destination == East ||
      m_destination == South)
	{
	  // Сразу устанавливаем новую позицию.
	  setWorldPos(dest);
	}
	setDirection(direction);
}

void Object::walkPath(const Path & path,
                      float velocity,
                      const std::string & endCallback)
{
  m_path.clear();

  // Назначаем путь.
  for (Path::const_reverse_iterator it = path.rbegin(); it != path.rend(); it++)
  {
    m_path.push_back(*it);
  }

  //  Пошли.
  if (!m_path.empty())
  {
    moveTo(m_path.at(m_path.size() - 1), velocity, endCallback);
  }

}

const Vector2 Object::getTileOffset() const
{
  if (UnknownDirection == m_destination)
    return Vector2(0.f, 0.f);

  // $TODO optimize?
  const float x = m_startVector.x * (1.f - m_moveLerp) + m_endVector.x * m_moveLerp;
  const float y = m_startVector.y * (1.f - m_moveLerp) + m_endVector.y * m_moveLerp;

  if (m_destination != SouthWest &&
      m_destination != SouthEast &&
      m_destination != East &&
      m_destination != South)
  {
    // Мы физически находимся на старом тайле
    return Vector2(x - m_startVector.x, y - m_startVector.y);
  }
  else
  {
    // Мы сразу были перемещены на новый тайл.
    return Vector2(x - m_endVector.x, y - m_endVector.y);
  }
}

//----------------------------------------------------------------------------------------------------------
void Object::setDirection(const int direction)
{
  // $TODO warning, not exception
  ACTS_CHECK(!m_spriteIndices.empty(), "Object has no appearance"); // Вообще нет никакого apperance!

  // Новое направление.
  m_direction = direction;

  bool   isPlaying = m_animation.isPlaying();
  bool   isLooped  = m_animation.isLooped();
  size_t frame     = m_animation.getCurrentFrame(); // $TODO check! not zero!

  // Меняем текущую анимацию.
  if (8 == m_spriteIndices.size())
  {
    size_t index = m_spriteIndices.at(static_cast<size_t>(m_direction));
    m_animation.setup(index);
  }
  else
    m_animation.setup(m_spriteIndices.at(0));

  if (isPlaying)
    m_animation.play(isLooped);
  m_animation.setCurrentFrame(frame);
}

const Point & Object::getWorldPos() const
{
  return m_worldPos;
}

Animation & Object::getAnimation()
{
  return m_animation;
}

void Object::setAppearance(const std::string & name, const int direction)
{
  const std::vector<size_t> & indices = AppearanceManager::getSingleton().getAppearance(name);
  m_spriteIndices.assign(indices.begin(), indices.end());
  setDirection(direction);

  // looks ugly
  // m_animation.setCurrentFrame(0);
}

void Object::setSimpleAppearance(const std::string & spriteName, const int direction)
{
  m_spriteIndices.clear();
  m_spriteIndices.push_back(ACTS_ST(SpriteManager).getSpriteIndex(spriteName));
  setDirection(direction);

  // looks ugly
  // m_animation.setCurrentFrame(0);
  //  m_animation.setCurrentFrame(0);
}

const bool Object::isVisible() const
{
  return m_visible;
}

void Object::setVisible(bool visible)
{
  m_visible = visible;
}

void Object::setLayer(size_t layer)
{
  m_layer = layer;
}

const size_t & Object::getLayer() const
{
  return m_layer;
}

const std::string Object::getName() const
{
  return m_name;
}

void Object::setName(const std::string & name)
{
  m_name = name;
}

void Object::setSelectionEnabled(bool enabled)
{
  m_selectionEnabled = enabled;
}

bool Object::selectionEnabled() const
{
  return m_selectionEnabled;
}

void Object::setColor(const TRS::Color & color)
{
  m_color = color;
}

const TRS::Color & Object::getColor() const
{
  return m_color;
}

Extras & Object::getExtras()
{
  return m_extras;
}

bool Object::blocksMovement() const
{
  return m_blocksMovement;
}

void Object::blockMovement(bool block)
{
  m_blocksMovement = block;
}

void Object::setTemporary(bool temp)
{
  m_temporary = temp;
}

bool Object::isTemporary() const
{
  return m_temporary;
}

} // namespace C4

*/