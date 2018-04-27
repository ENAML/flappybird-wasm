/**
 * -----------------------------------------------------------------------------
 * Common
 * -----------------------------------------------------------------------------
 */
#ifndef COMMON_H
#define COMMON_H


/**
 * Global Macros
 */
#define DEBUG				true
#define DRAW_STATS          false
#define SCREEN_H            600 //640 
#define SCREEN_W            400

#define FPS					60  // assumes 60fps
#define DELTA_TIME			(1.0 / FPS)


/**
 * External / 3rd Party Imports
 */
// C std
#include <stdlib.h> // Required for: malloc(), free(), rand()
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

// RayLib
#include "raylib.h"
// #include "raymath.h"
// #include "rlgl.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Utility
#include "util/package.hpp"


/**
 * -----------------------------------------------------------------------------
 * MISC
 * -----------------------------------------------------------------------------
 */



/**
 * for errors...
 */
inline void die(const char *message)
{
    perror(message);
    exit(1); 
}

/**
 * `println()` for easier logging...
 */
inline void println(const char *text, ...)
{
	va_list argp;
	
	va_start(argp, text);
	vfprintf(stdout, text, argp);
	va_end(argp);

	fputc('\n', stdout);
}

/**
 * trace logging
 */
inline void printlog(int msgType, const char *text, ...)
{
    va_list args;
    va_start(args, text);

    switch (msgType)
    {
        case 0: fprintf(stdout, "[ INFO ]: "); break;
        case 1: fprintf(stdout, "[ DEBUG ]: "); break;
        case 2: fprintf(stdout, "[ ERROR ]: "); break;
        case 3: fprintf(stdout, "[ WARNING ]: "); break;
        default: assert(false); break;
    }

    vfprintf(stdout, text, args);
    fprintf(stdout, "\n");

    va_end(args);

    if (msgType == 3) exit(1);
}



/**
 * TODO:
 * - seed with `srand()`
 * 	 - see: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
 */
namespace rng
{
	inline float rand()
	{
		static const float MAX = 10000000; // RAND_MAX; 

		// return (float)rand() / (float)RAND_MAX;
		return (float)GetRandomValue(0, MAX) / (float)MAX;
	}
	
	inline float range(float min, float max)
	{
		float range = max - min;
		float r = rng::rand();

		return min + (range * r);
	}
}


/**
 * Helper methods for Raylib converstion
 */
inline Vector2 rlVec2(float x, float y)
{
	return (Vector2){x , y};
}

inline Vector2 rlVec2(Vector2f v)
{
	return rlVec2(v.x, v.y);
}

inline Rectangle rlRect(float x, float y, float w, float h)
{
	return (Rectangle){(int)x,(int)y,(int)w,(int)h};
}
inline Rectangle rlRect(Vec2f pos, Vec2f size)
{
	// return (Rectangle){(int)pos.x, (int)pos.y, (int)size.width, (int)size.height};
	return rlRect(pos.x, pos.y, size.width, size.height);
}

inline Color rlColor(Color c)
{
	return c;
}


#endif /* COMMON_H */