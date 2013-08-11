#pragma once

#include "Logging/Logger.hxx"
#include "Logging/LogSection.hxx"

/// @file LogHelpers.hxx
/// @brief Some useful logger macros.

/// @def CORE4_LOG_MESSAGE(text)
/// Log a message.
#define CORE4_LOG_MESSAGE(text) \
  Core4::Logger::getSingleton().message(Core4::ILogListener::Message, text);

/// @def CORE4_LOG_ERROR(text)
/// Log an error.
#define CORE4_LOG_ERROR(text) \
  Core4::Logger::getSingleton().message(Core4::ILogListener::Error, text);

/// @def CORE4_LOG_INFO(text)
/// Log an informational message.
#define CORE4_LOG_INFO(text) \
  Core4::Logger::getSingleton().message(Core4::ILogListener::Info, text);

/// @def CORE4_LOG_WARNING(text)
/// Log a warning.
#define CORE4_LOG_WARNING(text) \
  Core4::Logger::getSingleton().message(Core4::ILogListener::Warning, text);

/// @def CORE4_LOG_WARNING(text)
/// Log something else.
#define CORE4_LOG_OTHER(text) \
  Core4::Logger::getSingleton().message(Core4::ILogListener::Other, text);

/// @def CORE4_LOG_SECTION(index)
/// @see LogSection.
/// @param name Section name.
#define CORE4_LOG_SECTION(name) Core4::LogSection logSectionInstance##__LINE__(name);

