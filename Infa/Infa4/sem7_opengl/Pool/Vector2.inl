#pragma once

inline float Vector2::Len() const
{
  return sqrt(x * x + y * y);
}

inline float Vector2::SquareLen() const
{
  return x * x + y * y;
}

inline void Vector2::Normalize()
{
  float l = sqrtf(x * x + y * y);
  if (fabs(l) > float(1e-8))
  {
    float k = float(1.0) / l;
    x *= k;
    y *= k;
  }
}

inline void Vector2::Invert()
{
  x = -x;
  y = -y;
}

inline void Vector2::Rotate(float angle)
{
  Vector2 self = *this;
  Vector2 x = self;
  Vector2 y = Vector2(-x.y, x.x);
  Vector2 delta = x * cos(angle) + y * sin(angle) - x;
  self += delta;
  *this = self;
}

inline Vector2 Vector2::GetNorm() const
{
  float l = sqrt(x * x + y * y);
  if (fabs(l) > float(1e-8))
  {
    float k = float(1.0) / l;
    return Vector2(x * k, y * k);
  }else
  {
    return Vector2(0, 0);
  }
}
  
inline Vector2 Vector2::operator-() const
{
  return Vector2(-x, -y);
}

inline void Vector2::Decrease(float val)
{
  if(SquareLen() > val * val)
  {
    float len = Len();
    float scale = (len - val) / len;
    x *= scale;
    y *= scale;
  }else
  {
    x = y = 0.0f;
  }
}
  
//mul number
inline Vector2& Vector2::operator *=(float t)
{
  x *= t;
  y *= t;
  return *this;
}

//div number
inline Vector2& Vector2::operator /=(float t)
{
  float inv = float(1.0) / t;
  x *= inv;
  y *= inv;
  return *this;
}

inline Vector2& Vector2::operator +=(const Vector2 &v)
{
  x += v.x;
  y += v.y;
  return *this;
}

inline Vector2& Vector2::operator-=(const Vector2 &V)
{
  x -= V.x;
  y -= V.y;
  return *this;
}

inline Vector2 Vector2::operator+(const Vector2& v) const
{
  return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2& v) const
{
  return Vector2(x - v.x, y - v.y);
}

inline float Vector2::operator*(const Vector2& v) const
{
  return x * v.x + y * v.y;
}

inline Vector2 Vector2::operator*(float d) const
{
  return Vector2(x * d, y * d);
}

inline Vector2 Vector2::GetPerpendicular() const
{
  return Vector2(-y, x);
}

inline Vector2 operator*(float t, const Vector2& v)
{
  return Vector2(v.x * t, v.y * t);
}

inline Vector2 Vector2::operator/(float t) const
{
  float invd;
  if(fabs(t) > float(1e-8)) invd = float(1.0) / t;
  return Vector2(x * invd, y * invd);
}

inline float Vector2::operator^(const Vector2 &v) const
{
    return x * v.y - y * v.x;
}
