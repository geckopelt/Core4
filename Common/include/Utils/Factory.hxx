#pragma once

/// @file Factory.hxx
/// @brief Factory template.

#include <list>

namespace Core4
{

/// A simple factory pattern implementation.
template <typename KeyType, typename InterfaceType> class Factory
{
  template <typename ClassType> static InterfaceType * Spawner()
  {
    return new ClassType();
  }

  typedef InterfaceType * SpawnerFn();
  typedef std::map<KeyType, SpawnerFn*> SpawnersMap;
public:

  /// Register a type in this factory.
  /// @param id Class type identifier.
  template <typename ClassType> void reg(const KeyType & id)
  {
    m_spawners[id] = &Spawner<ClassType>;
  }

  /// Unregister a type.
  /// @param id Class type identifier.
  void unreg(const KeyType & id)
  {
    m_spawners.erase(id);
  }

  /// Create an instance of a class.
  /// @note Don't forget to delete it!
  /// @param id Class type identifier.
  /// @return Pointer to class instance or NULL.
  InterfaceType * create(const KeyType & id)
  {
  	typename SpawnersMap::iterator it = m_spawners.find(id);
  	return (it != m_spawners.end()) ? it->second() : NULL;
  }

  /// Enumerate all class types registered.
  /// @param available A list to fill.
  void enumAvailable(std::list<KeyType> & available) const
  {
  	available.clear();
  	for (typename SpawnersMap::const_iterator it = m_spawners.begin();
         it != m_spawners.end(); it++)
	    available.push_back(it->first);
  }
private:
  SpawnersMap m_spawners;
};

} // namespace Core4
