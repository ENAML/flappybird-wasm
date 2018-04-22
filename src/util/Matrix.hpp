#pragma once


class Matrix2x2f;
class Matrix4x4f;

Matrix2x2f operator *(const Matrix2x2f& m1, const Matrix2x2f& m2);

class Matrix2x2f
{
public:
    Vector2f value[2];

public:
    //Array subscript operator
	Vector2f& operator [](const size_t i) { assert(i < 2); return value[i]; }
	const Vector2f& operator [](const size_t i) const { assert(i < 2); return value[i]; }

    // Arithmetic operators
    Matrix2x2f operator +(const Matrix2x2f& b) const
    {
        return Matrix2x2f(value[0] + b[0],
                          value[1] + b[1]);
    }

    Matrix2x2f operator +(const float& b) const
    {
        return Matrix2x2f(value[0] + Vector2f(b),
                          value[1] + Vector2f(b));
    }

    Matrix2x2f operator *(const float& b) const
    {
        return Matrix2x2f(value[0] * b,
                          value[1] * b);
    }

    Matrix2x2f operator /(const float& b) const
    {
        return Matrix2x2f(value[0] / b,
                          value[1] / b);
    }

    // Comparison / relational operators
    bool operator ==(const Matrix2x2f& b) const
    {
        return  (value[0] == b[0]) &&
                (value[1] == b[1]);
    }

    // Aliased Multiplication assignment rules
    Matrix2x2f& operator *=(const Matrix2x2f& b)    { *this = *this * b; return *this; }
    // Aliased Arithmetic and Comparison operators
    bool operator !=(const Matrix2x2f& b) const     { return !(*this == b); }

public:
    explicit Matrix2x2f()
    {
        value[0] = Vector2f(1, 0);
        value[1] = Vector2f(0, 1);
    }

    explicit Matrix2x2f(const Vector2f& c0, const Vector2f& c1)  // Column constructor
    {
        value[0] = c0;
        value[1] = c1;
    }

    explicit Matrix2x2f(const float& n)  // Diagonal constructor
    {
        value[0] = Vector2f(n, 0);
        value[1] = Vector2f(0, n);
    }

public:
    // Matrix functions
    Matrix2x2f   transpose() const
    {
        return Matrix2x2f(Vector2f(value[0].x, value[1].x),
                           Vector2f(value[0].y, value[1].y));
    }
	float determinant() const
    {
        return value[0].x * value[1].y - value[0].y * value[1].x;
    }

	Matrix2x2f   inverse() const
    {
        return Matrix2x2f(Vector2f( value[1].y, -value[0].y),
                           Vector2f(-value[1].x,  value[0].x)) / determinant();
    }
};

Vector2f   operator *(const Matrix2x2f& m,  const Vector2f& rt);
Vector2f   operator *(const Vector2f& ct,   const Matrix2x2f& m);
Matrix2x2f operator *(const Matrix2x2f& m1, const Matrix2x2f& m2);

class Matrix4x4f
{
public:
    Vector4f value[4];

public:
    //Array subscript operator
	Vector4f& operator [](const size_t i) { assert(i < 4); return value[i]; }
	const Vector4f& operator [](const size_t i) const { assert(i < 4); return value[i]; }

public:
    explicit Matrix4x4f(const float& n)  // Diagonal constructor
    {
        value[0] = Vector4f(n, 0, 0, 0);
        value[1] = Vector4f(0, n, 0, 0);
        value[2] = Vector4f(0, 0, n, 0);
        value[3] = Vector4f(0, 0, 0, n);
    }

public:
    static Matrix4x4f ortho(const float &left, const float &right, const float &bottom, const float &top)
    {
        Matrix4x4f Result(1);

        Result[0][0] = 2.0f / (right - left);
        Result[1][1] = 2.0f / (top - bottom);
        Result[2][2] = - 1.0f;
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        
        return Result;
    }
};

