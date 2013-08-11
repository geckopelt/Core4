#pragma once

/// @file LogSection.hxx
/// @brief A helper class which automatically handles log indentation

#include <string>

namespace Core4
{
    /// A helper class which automatically handles log indentation sections.
    class LogSection
    {
    public:
        /// Ctor. Begins a log section.
        /// @param id Log section id (name)
        LogSection(const std::string & id);

        // Dtor.
        virtual ~LogSection();
    private:
        std::string m_id;
    };

} // namespace Core4
