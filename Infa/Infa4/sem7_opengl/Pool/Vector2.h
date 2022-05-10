#pragma once
#include <iostream>
#include <math.h>

struct Vector2
{
  float x, y;

  Vector2();
  Vector2(float x, float y);

  float Len()       const;
  float SquareLen() const;
  void Normalize();
  Vector2 GetNorm() const;
  void Decrease(float val);

  void Invert();
  void Rotate(float angle);
  Vector2 operator-() const;

  Vector2& operator +=(const Vector2& v);
  Vector2& operator -=(const Vector2& v);
  Vector2& operator *=(float t);
  Vector2& operator /=(float t);

  Vector2 operator *(float t) const;
  Vector2 operator /(float t) const;

  Vector2 operator +(const Vector2& v) const;
  Vector2 operator -(const Vector2& v) const;

  float operator *(const Vector2& v) const;
  float operator ^(const Vector2& v) const;

  Vector2 GetPerpendicular() const;
};

Vector2 operator *(float t, const Vector2& v);

std::ostream& operator <<(std::ostream& s, const Vector2& v);
std::istream& operator >>(std::istream& s, Vector2& v);

float Square(const Vector2& p0, const Vector2& p1, const Vector2& p2);

#include "Vector2.inl"
