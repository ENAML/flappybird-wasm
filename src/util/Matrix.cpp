#include "util/package.hpp"


Vector2f   operator *(const Matrix2x2f& m,  const Vector2f& rt)   { return rt * m.transpose(); }
Vector2f   operator *(const Vector2f& ct,   const Matrix2x2f& m)  { return Vector2f(ct.dot(m[0]), ct.dot(m[1])); }
Matrix2x2f operator *(const Matrix2x2f& m1, const Matrix2x2f& m2) { return Matrix2x2f(m1 * m2[0], m1 * m2[1]); }

