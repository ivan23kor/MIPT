#include "Vector2.h"

Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y): x(x), y(y) 
{
}

std::ostream& operator <<(std::ostream& s, const Vector2& v)
{
  s << v.x << " " << v.y << std::endl;
  return s;
}

std::istream& operator >>(std::istream& s, Vector2& v)
{
  s >> v.x >> v.y;
  return s;
}

float Square(const Vector2& p0, const Vector2& p1, const Vector2& p2)
{
  return 0.5f * (p1 - p0) ^ (p2 - p0);
}
