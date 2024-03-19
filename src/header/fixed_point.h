#ifndef FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_
#define FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_

#include <cstdint>

class FixedPoint {
 public:
  FixedPoint(int32_t value, int32_t exp);

  void operator+(FixedPoint other);

  void operator-();
  
  void operator-(FixedPoint other);

  void operator*(FixedPoint other);

  void operator/(FixedPoint other);

  int32_t exp_;

  int32_t value_;
};

#endif  // FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_
