#pragma once

#include <math.h>

const float pi = 3.14159265f;

template <typename T>
T Sqr(const T& value)
{
  return value * value;
}

template <typename T>
T Sign(const T& value)
{
  return value < T(0) ? T(-1) : T(1);
}
