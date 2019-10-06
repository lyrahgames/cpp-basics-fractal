#pragma once
#include <iostream>

namespace me {

struct complex {
  complex(float r, float i) : real{r}, imag{i} {}
  // explicit complex(float r) : complex{r, 0} {}
  complex(float r) : complex{r, 0} {}
  complex() = default;

  float real{};
  float imag{};
};

inline float squared_norm(complex c) {
  return c.real * c.real + c.imag * c.imag;
}

inline complex operator*(complex c1, complex c2) {
  return {c1.real * c2.real - c1.imag * c2.imag,
          c1.real * c2.imag + c1.imag * c2.real};
}

inline complex operator+(complex c1, complex c2) {
  return {c1.real + c2.real, c1.imag + c2.imag};
}

inline std::ostream& operator<<(std::ostream& os, complex z) {
  return os << z.real << " + " << z.imag << "i";
}

}  // namespace me