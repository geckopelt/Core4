/// @file Guards.hxx
/// @brief Useful guard macros

#pragma once

#include <string>
#include "Exceptions/GenericException.hxx"

/// @def CORE4_CHECK(condition, msg)
/// Throws a GenericException in case of false condition.
#define CORE4_CHECK(condition, msg) \
  if (!(condition)) \
  { \
    throw GenericException( \
      std::string(#condition) + \
      std::string(" at ") + \
      std::string(__FILE__) + \
      std::string(", ") + \
      std::string(__FUNCTION__) +\
      std::string("(): ") + \
      std::string(msg)); \
  }
