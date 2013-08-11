#pragma once

/// @file BuildInfo.hxx
/// @brief Build info macros.

#if defined C4_APP_DEBUG
  #define C4_BUILD_INFO "Core4 Debug ["__DATE__", " __TIME__"]"
#else
  #define C4_BUILD_INFO "Core4 Release ["__DATE__", " __TIME__"]"
#endif
