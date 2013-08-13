#pragma once

/// @file Light.hxx
/// @brief A light source.

#include <TinyXML.h>
#include "Serialization/Serializeable.hxx"
#include "Types/Vector2.hxx"

namespace Core4
{
    /// An isometric pseudo light source. Modifies tile corner colors.
    /// Can also be used for "fog" effects.
    class Light : public Serializeable
    {
    public:
        /// Ctor. Initializes everything.
        Light();

        /// Set light components.
        /// @param red Red color component.
        /// @param green Green color component.
        /// @param blue Blue color component.
        /// @param fog Fog component. 0 is no fog, 255 is maximum fog.
        void setComponents(int red, int green, int blue, int fog);

        /// Get red component.
        int red() const;

        /// Get green component.
        int green() const;

        /// Get blue component.
        int blue() const;

        /// Get fog component.
        int fog() const;

        /// Set global position.
        /// @param pos Global position.
        void setMapPos(const Vector2 & pos);
        
        /// Get global position.
        /// @return Global position.
        const Vector2 & getMapPos() const;

        /// Enable or disable light.
        /// @param enable Yes or no.
        void enable(bool enable);
        
        /// Is light enabled?
        /// @return true if enabled.
        bool isEnabled() const;

        /// Set light range.
        /// @param range Light range, in pixels.
        void setRange(int range);

        /// Get light range.
        /// @return Light range, in pixels.
        int  getRange() const;
        
        /// @see Serializeable
        void perform(TiXmlElement & element, const SerializeActionType action);
    private:
        int     m_red;
        int     m_green;
        int     m_blue;
        int     m_fog;
        Vector2 m_mapPos;
        bool    m_enabled;
        int     m_range;
    };
} // namespace Core4
