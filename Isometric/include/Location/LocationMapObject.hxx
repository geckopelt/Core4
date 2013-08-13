#pragma once

/// @file LocationMapObject.hxx
/// @brief An object at location map.

#include "TypesC4Types.hxx"
#include "C4Animation.hxx"
#include "Serialization/Serializeable.hxx"
#include "C4SerializationUtils.hxx"
#include "C4SquirrelUtils.hxx"
#include "C4Extras.hxx"
#include "C4SimplePathfinder.hxx"

#include "Sprites/Animation.hxx"
#include "Location/IsoDirection.hxx"

/* TODO

namespace Core4
{
    /// An object (A wall, a tree, a critter, everything).
    class Object : public Serializeable
    {
    public:
        /// Ctor. Initializes everything.
        Object();

        /// Dtor.
        virtual ~Object();

        /// Update an object.
        /// @param dt Update interval.
        virtual void update(float dt);

        /// Set current direction.
        /// @param direction Current isometric direction.
        void setDirection(const IsoDirection direction);

        /// Get current direection.
        /// @return Current isometric direction.
        IsoDirection getDirection() const;

        /// Get map position.
        /// @return Map position.
        const Point &   getWorldPos() const;

        /// Get current tile offset, in pixels.
        /// @return Current tile offset, in pixels.
        const Vector2 getTileOffset() const;

        Animation & getAnimation();
        
        void setAppearance(const std::string & name, const int direction);
        
        void setSimpleAppearance(const std::string & spriteName, const int direction);

        /// ������� �� �������� ����.
        /// @param direction ����������� ��������.
        /// @param velocity �������� ��������, �/�. ���� ���� - 1x1 �.
        /// @param endCallback ��� ����������-�������, ������� ����� �������, ����� ������ �������� �����������,
        /// � �������� ��������� ����� �������� ��� ���.
        void moveTo(const int direction, float velocity, const std::string & endCallback);

        /// ����� �� ��������� ����
        /// @param path ����
        /// @param velocity ��������, � ������� ������
        /// @param endCallback ��� ����������-�������, ������� ����� �������, ����� ������ �������� �����������,
        void walkPath(const Path & path, float velocity, const std::string & endCallback);

        const bool isVisible() const;
        void setVisible(bool visible);

        void setLayer(size_t layer);
        const size_t & getLayer() const;

        // $TMP?
        void setWorldPos(const Point & pos);

        const std::string getName() const;
        void setName(const std::string & name);

        void setSelectionEnabled(bool enabled);
        bool selectionEnabled() const;

        void setColor(const Color & color);
        const Color & getColor() const;

  C4_SERIALIZATION
  {
    C4_SERIALIZE_ATTR(m_name);
    C4_SERIALIZE_CHILD(m_worldPos,   "worldPos");
    C4_SERIALIZE_CHILD(m_tileOffset, "tileOffset");

    C4_SERIALIZE_CHILD(m_startVector, "startVector");
    C4_SERIALIZE_CHILD(m_endVector,   "endVector");
    C4_SERIALIZE_ATTR(m_moveLerp);

    C4_SERIALIZE_ATTR(m_direction);
    C4_SERIALIZE_ATTR(m_destination);
    C4_SERIALIZE_ATTR(m_velocity);
    C4_SERIALIZE_ATTR(m_visible);
    C4_SERIALIZE_ATTR(m_spriteIndices);
    C4_SERIALIZE_ATTR(m_endCallback);
    C4_SERIALIZE_ATTR(m_blocksMovement);
    C4_SERIALIZE_ATTR(m_selectionEnabled);
    C4_SERIALIZE_ATTR(m_color);

    C4_SERIALIZE_ATTR(m_path);

    C4_SERIALIZE_CHILD(m_animation, "animation");
    C4_SERIALIZE_CHILD(m_extras,    "extras");
  }

  bool serializeable() const
  {
    return !m_temporary;
  }

  Extras & getExtras();

  // $TODO move to cpp
  const std::vector<size_t> & getSpriteIndices() const { return m_spriteIndices; }

  bool blocksMovement() const;
  void blockMovement(bool block);

  void setTemporary(bool temp);
  bool isTemporary() const;
private:
  bool                               m_temporary;     /// ��������� ������?
  size_t                             m_layer;
  std::string                        m_name;           ///< ���������� ��� �������.
  Point                              m_worldPos;       ///< ������� ������� �� ����� ���� (� ������).
  Vector2                            m_tileOffset;     ///< ������� �������� ������������ ����� (� ��������).

  Vector2                            m_startVector;    /// $TODO! comment?
  Vector2                            m_endVector;
  float                              m_moveLerp;

  int                                m_direction;        ///< ���� "�������" ������.
  int                                m_destination;      ///< � ������ ��������� ����� �������� ������ (�����������).
  float                              m_velocity;         ///< ������� �������� (�/�).
  bool                               m_visible;
  std::vector<size_t>                m_spriteIndices;    ///< ������� �������� ��� ���� �����������.
  Animation                          m_animation;        ///< �������� ��� �������.
  std::string                        m_endCallback;      ///< $TODO comment
  bool                               m_blocksMovement;   ///< ����� ������ ������ ������
  bool                               m_selectionEnabled; ///< ����� �� ������� ������ �����?
  TRS::Color                         m_color;            ///< ���� �������.
  Extras                             m_extras;           ///< �������������� ��������.
  std::vector<size_t>                m_path;             ///< ������� ����.
};

} // namespace C4

DECLARE_INSTANCE_TYPE_NAME(C4::Object, Object)

*/