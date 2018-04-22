#pragma once


class Vector4f;
class Matrix2x2f;
class Matrix4x4f;

class Vector2f
{
public:
    union
    {
        float value[2];
        struct { float x, y; };
        struct { float r, g; };
        struct { float s, t; };
        struct { float width, height; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 2); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 2); return value[i]; }

    //Arithmetic operators
    Vector2f operator +(const Vector2f& b) const { return Vector2f(x + b.x, y + b.y); }
    Vector2f operator -(const Vector2f& b) const { return Vector2f(x - b.x, y - b.y); }
    Vector2f operator *(const Vector2f& b) const { return Vector2f(x * b.x, y * b.y); }
    Vector2f operator /(const Vector2f& b) const { return Vector2f(x / b.x, y / b.y); }
    Vector2f operator -() const /* Unary minus */ { return Vector2f(-x, -y); }
    Vector2f operator *(const float& b) const { return Vector2f(x * b, y * b); }
    Vector2f operator /(const float& b) const { return Vector2f(x / b, y / b); }

    bool operator ==(const Vector2f& b) const { return (x == b.x) && (y == b.y); }
    bool operator !=(const Vector2f& b) const { return !(*this == b); }

    //Arithmetic assignment operators
    Vector2f& operator +=(const Vector2f& b) { *this = *this + b; return *this; }
    Vector2f& operator -=(const Vector2f& b) { *this = *this - b; return *this; }
    Vector2f& operator *=(const Vector2f& b) { *this = *this * b; return *this; }
    Vector2f& operator /=(const Vector2f& b) { *this = *this / b; return *this; }
    Vector2f& operator *=(const float& b) { *this = *this * b; return *this; }
    Vector2f& operator /=(const float& b) { *this = *this / b; return *this; }

public:
    explicit Vector2f() : x(0), y(0) { }
    explicit Vector2f(const float& n) : x(n), y(n) { }
    explicit Vector2f(const float& nx, const float& ny) : x(nx), y(ny) { }

public:
    // Geometric functions
    float         length() const;
    float         lengthSquared() const;
    float         distance(const Vector2f &p1) const;
    float         distanceSquared(const Vector2f &p1) const;
    float         dot(const Vector2f &v2) const;
    Vector2f     normalize() const;
};

Vector2f operator* (const float &s, const Vector2f &v);

class Vector3f
{
public:
    union
    {
        float value[3];
        struct { float x, y, z; };
        struct { float r, g, b; };
        struct { float s, t, p; };
        struct { float width, height, depth; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 3); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 3); return value[i]; }

    //Arithmetic operators
    Vector3f operator +(const Vector3f& b) const { return Vector3f(x + b.x, y + b.y, z + b.z); }
    Vector3f operator -(const Vector3f& b) const { return Vector3f(x - b.x, y - b.y, z - b.z); }
    Vector3f operator *(const Vector3f& b) const { return Vector3f(x * b.x, y * b.y, z * b.z); }
    Vector3f operator /(const Vector3f& b) const { return Vector3f(x / b.x, y / b.y, z / b.z); }
    Vector3f operator -() const /* Unary minus */ { return Vector3f(-x, -y, -z); }
    Vector3f operator *(const float& b) const { return Vector3f(x * b, y * b, z * b); }
    Vector3f operator /(const float& b) const { return Vector3f(x / b, y / b, z / b); }
    
    bool operator ==(const Vector3f& b) const { return (x == b.x) && (y == b.y) && (z == b.z); }
    bool operator !=(const Vector3f& b) const { return !(*this == b); }
    
    //Arithmetic assignment operators
    Vector3f& operator +=(const Vector3f& b) { *this = *this + b; return *this; }
    Vector3f& operator -=(const Vector3f& b) { *this = *this - b; return *this; }
    Vector3f& operator *=(const Vector3f& b) { *this = *this * b; return *this; }
    Vector3f& operator /=(const Vector3f& b) { *this = *this / b; return *this; }
    Vector3f& operator *=(const float& b) { *this = *this * b; return *this; }
    Vector3f& operator /=(const float& b) { *this = *this / b; return *this; }
    
public:
    explicit Vector3f() : x(0), y(0), z(0) { }
    explicit Vector3f(const float& n) : x(n), y(n), z(n) { }
    explicit Vector3f(const float& nx, const float& ny, const float& nz) : x(nx), y(ny), z(nz) { }

public:
    // Geometric functions
	float       length() const;
    float       lengthSquared() const;
    float       distanceSquared(const Vector3f &p1) const;
	float       distance(const Vector3f &p1) const;
    float       dot(const Vector3f &v2) const;
    Vector3f   cross(const Vector3f &y) const;
	Vector3f   normalize() const;
};

Vector3f operator* (const float &s, const Vector3f &v);

class Vector4f
{
public:
    union
    {
        float value[4];
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        struct { float s, t, p, q; };
    };

    //Array subscript operator
	float& operator [](const size_t i) { assert(i < 4); return value[i]; }
	const float& operator [](const size_t i) const { assert(i < 4); return value[i]; }

    //Arithmetic operators
    Vector4f operator +(const Vector4f& b) const { return Vector4f(x + b.x, y + b.y, z + b.z, w + b.w); }
    Vector4f operator -(const Vector4f& b) const { return Vector4f(x - b.x, y - b.y, z - b.z, w - b.w); }
    Vector4f operator *(const Vector4f& b) const { return Vector4f(x * b.x, y * b.y, z * b.z, w * b.w); }
    Vector4f operator /(const Vector4f& b) const { return Vector4f(x / b.x, y / b.y, z / b.z, w / b.w); }
    Vector4f operator -() const /* Unary minus */ { return Vector4f(-x, -y, -z, -w); }
    Vector4f operator *(const float& b) const { return Vector4f(x * b, y * b, z * b, w * b); }
    Vector4f operator /(const float& b) const { return Vector4f(x / b, y / b, z / b, w / b); }
    
    bool operator ==(const Vector4f& b) const { return (x == b.x) && (y == b.y) && (z == b.z) && (w == b.w); }
    bool operator !=(const Vector4f& b) const { return !(*this == b); }
    
    //Arithmetic assignment operators
    Vector4f& operator +=(const Vector4f& b) { *this = *this + b; return *this; }
    Vector4f& operator -=(const Vector4f& b) { *this = *this - b; return *this; }
    Vector4f& operator *=(const Vector4f& b) { *this = *this * b; return *this; }
    Vector4f& operator /=(const Vector4f& b) { *this = *this / b; return *this; }
    Vector4f& operator *=(const float& b) { *this = *this * b; return *this; }
    Vector4f& operator /=(const float& b) { *this = *this / b; return *this; }
    
public:
    explicit Vector4f() : x(0), y(0), z(0), w(0) { }
    explicit Vector4f(const float& n) : x(n), y(n), z(n), w(n) { }
    explicit Vector4f(const float& nx, const float& ny, const float& nz, const float& nw) : x(nx), y(ny), z(nz), w(nw) { }
    explicit Vector4f(const Vector3f& v, const float& nw) : x(v.x), y(v.y), z(v.z), w(nw) { }

public:
    // Geometric functions
	float       length() const;
    float       lengthSquared() const;
	float       distance(const Vector4f &p1) const;
    float       distanceSquared(const Vector4f &p1) const;
    float       dot(const Vector4f &v2) const;
	Vector4f   normalize() const;
};

Vector4f operator* (const float &s, const Vector4f &v);


typedef Vector2f Vec2f;
typedef Vector3f Vec3f;
typedef Vector4f Vec4f;

typedef Vector2f Point2f;
typedef Vector3f Point3f;
typedef Vector4f Point4f;

typedef Vector2f TexCoord2f;

typedef Vector3f Color3f;
typedef Vector4f Color4f;

typedef Vector2f tDimension2f;

