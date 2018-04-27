#pragma once

#include <math.h>
#include "util/Vector.hpp"


// avoid conflicting definition from raylib
#undef PI

class Math
{
public:
    // A mathematical constant for the ratio of the circumference of a
    // circle to its diameter, expressed as pi, with a value of 3.141592653589793.
    static const float PI;       

public:
    // Angle and trigonometric functions
    static float radians(const float &degrees)
    {
        return degrees * (PI / 180.0f);
    }

    static float degrees(const float &radians)
    {
        return radians * (180.0f / PI);
    }
    
    static float atan2(float y, float x)
    {
        return atan2f(y, x);
    }

    static float atan2(Vec2f v)
    {
        return atan2f(v.y, v.x);
    }

    // Exponential functions
    static float roundPow2(const float &x)
    {
        if (x > 0)
        {
            return 1 << uint32_t(log2(float(x - 1)) + 1);
        }
        
        return 1;
    }

    // Common functions
    static float min(const float &x, const float &y)
    {
        return (x < y) ? x : y;
    }
    static float max(const float &x, const float &y)
    {
        return (x > y) ? x : y;
    }
    static float clamp(const float &x, const float &minVal, const float &maxVal)
    {
        return max(min(x, maxVal), minVal);
    }
    // static float mix(float const & x, float const & y, float const & a)
    // {
    //     return float(float(x) + a * float(y - x));
    // }

    // returns value btwn 'src' and 'dest'
    static float lerp(const float& pct, const float& src, const float& dest)
    {
        return src + (dest - src)*pct;
    }

    // maps 'srcVal' in range [srcMin, srcMax] to range [destMin, destMax]
    static float map(
        const float& srcVal,
        const float& srcMin, const float& srcMax,
        const float& destMin, const float& destMax
    ) {
        auto pct = (srcVal - srcMin) / (srcMax - srcMin);
        return lerp(pct, destMin, destMax);
    }
};
