#include "util/package.hpp"


Vector2f operator* (const float &s, const Vector2f &v) { return v * s; }
Vector3f operator* (const float &s, const Vector3f &v) { return v * s; }
Vector4f operator* (const float &s, const Vector4f &v) { return v * s; }

float Vector2f::length() const { return sqrtf(lengthSquared()); }
float Vector3f::length() const { return sqrtf(lengthSquared()); }
float Vector4f::length() const { return sqrtf(lengthSquared()); }

float Vector2f::lengthSquared() const { return dot(*this); }
float Vector3f::lengthSquared() const { return dot(*this); }
float Vector4f::lengthSquared() const { return dot(*this); }

float Vector2f::distance(const Vector2f &p1) const { return sqrtf((*this).distanceSquared(p1)); }
float Vector3f::distance(const Vector3f &p1) const { return sqrtf((*this).distanceSquared(p1)); }
float Vector4f::distance(const Vector4f &p1) const { return sqrtf((*this).distanceSquared(p1)); }

float Vector2f::distanceSquared(const Vector2f &p1) const { return (p1 - (*this)).lengthSquared(); }
float Vector3f::distanceSquared(const Vector3f &p1) const { return (p1 - (*this)).lengthSquared(); }
float Vector4f::distanceSquared(const Vector4f &p1) const { return (p1 - (*this)).lengthSquared(); }

float Vector2f::dot(const Vector2f &v2) const { return x * v2.x + y * v2.y; }
float Vector3f::dot(const Vector3f &v2) const { return x * v2.x + y * v2.y + z * v2.z; }
float Vector4f::dot(const Vector4f &v2) const { return x * v2.x + y * v2.y + z * v2.z + w * v2.w; }

Vector3f Vector3f::cross(const Vector3f &v2) const
{
    return Vector3f(y * v2.z - z * v2.y,
                     z * v2.x - x * v2.z,
                     x * v2.y - y * v2.x);
}

Vector2f Vector2f::normalize() const { return (*this) / length(); }
Vector3f Vector3f::normalize() const { return (*this) / length(); }
Vector4f Vector4f::normalize() const { return (*this) / length(); }

