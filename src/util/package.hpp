#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

/**
 * debugging / assert
 */
#if DEBUG
#include <assert.h>
#else
#ifdef assert
#undef assert
#endif
#define assert(x) { }
#endif



//Some standard headers from C and C++
#include <bitset>
#include <math.h>


//Patterns
#include "events.hpp"
#include "Optional.hpp"

//Math
#include "Math.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Rect.hpp"

//System Time, Input, and Audio
// #include "Timer.hpp"
