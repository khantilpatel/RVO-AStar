#include <glm/glm.hpp>
//using namespace glm;
#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H



inline float distance_absSq(glm::vec3 a, glm::vec3 b)
{
	return glm::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

 inline float sqr(float a) {
    return a*a;
  }

 inline float absSq(const glm::vec2& q) { return q.x * q.x + q.y * q.y; }

 inline float abs(const glm::vec2& q) { return std::sqrt(absSq(q)); }


 /*! \param p A vector
    \param q A vector
    \returns Returns the determinant of the 2x2 matrix formed by using p as the upper row and q as the lower row. */
inline float det(const glm::vec2& p, const glm::vec2& q) { return p.x*q.y - p.y*q.x; }


/*! Dot product.
    \param q The right hand side vector
    \returns The dot product of the lhs vector and the rhs vector.  */
inline float dotproduct(const glm::vec2& p, const glm::vec2& q) { return p.x * q.x + p.y * q.y; }


#endif