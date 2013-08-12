#pragma once

/// @file Direct3DCommon.hxx
/// @brief Common Direct3D includes & macros

#include <d3d9.h>

#define SAFE_RELEASE(x) if (NULL != (x)) { (x)->Release(); (x) = NULL; }
