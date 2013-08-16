#pragma once

/// @file Path.hxx
/// @brief A path to walk.

#include <vector>
#include "Location/IsoDirection.hxx"

namespace Core4
{
    typedef std::vector<IsoDirection> Path; //< Isometric path to walk.
} // namespace Core4