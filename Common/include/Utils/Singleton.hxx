#pragma once

/// @file Singleton.hxx
/// @brief Meyers Singleton template

namespace Core4
{

#define CORE4_SINGLE(type) type::getSingleton()

/// A simple Meyers singleton.
template <typename ClassName> struct Singleton
{
  /// Get a reference of an instance.
  /// @return ClassName's instance.
  static ClassName & getSingleton()
  {
    static ClassName instance;
    return instance;
  }
};

} // namespace Core4    
