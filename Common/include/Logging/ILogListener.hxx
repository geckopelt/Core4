#pragma once

/// @file ILogListener.hxx
/// @brief Log listener interface

#include <string>

namespace Core4
{
    /// Log listener interface.
    struct ILogListener
    {
        /// Log message type.
        enum Type
        {
            Message, //< A simple trace message.
            Error,   //< An error.
            Info,    //< Some sort of an important information.
            Warning, //< Warning.
            Other    //< Something else.
        };

        /// Called on every message logged.
        /// @param type Message type.
        /// @param indent Indentation, in spaces.
        /// @param text Message text.
        virtual void message(const Type type, const size_t indent, const std::string & text) = 0;

        virtual ~ILogListener() {};
    };
} // namespace Core4
