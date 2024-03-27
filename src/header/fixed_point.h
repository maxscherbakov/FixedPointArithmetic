#ifndef FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_
#define FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_


template<uint8_t fraction_bits=16>
class FixedPoint {
 public:
  FixedPoint(float value) {
    value_ = (int32_t)(std::round((double)value * (1 << fraction_bits)));
  }

  float GetFloat() {
    return (float)((double)value_ / (1 << fraction_bits));
  }

  int32_t GetInt() const {
    return value_;
  }


  template<uint8_t other_fb>
  void operator+=(const FixedPoint<other_fb>& other) {
    value_= (int32_t)((int64_t)value_ + ValueConversion(other));
  }


  template<uint8_t other_fb>
  FixedPoint operator+(const FixedPoint<other_fb>& other) {
    FixedPoint<fraction_bits> result = *this;
    result += other;

    return result;
  }


  template<uint8_t other_fb>
  void operator-=(const FixedPoint<other_fb>& other) {
    value_= (int32_t)((int64_t)value_ - ValueConversion(other));
  }
  
  FixedPoint operator-() {
    FixedPoint<fraction_bits> result = *this;
    result.value_ = -result.value_;
    
    return result;
  }

  template<uint8_t other_fb>
  FixedPoint operator-(const FixedPoint<other_fb>& other) {
    FixedPoint<fraction_bits> result = *this;
    result -= other;

    return result;
  }

  template<uint8_t other_fb>
  void operator*=(const FixedPoint<other_fb>& other) {
    value_ = (int32_t)((int64_t)value_ * other.GetInt() >> other_fb);
  }


  template<uint8_t other_fb>
  FixedPoint operator*(const FixedPoint<other_fb>& other) {
	
    FixedPoint<fraction_bits> result = *this;
    result *= other;
	

    return result;
  }

  template<uint8_t other_fb>
  void operator/=(const FixedPoint<other_fb>& other) {
    value_ = (int32_t)((int64_t)value_ / other.GetInt()) << other_fb;
  }

  template<uint8_t other_fb>
  FixedPoint operator/(const FixedPoint<other_fb>& other) {
    FixedPoint<fraction_bits> result = *this;
    result /= other;

    return result;
  }

 private:
  template<uint8_t other_fb>
  constexpr int32_t ValueConversion(const FixedPoint<other_fb>& other) {
    int64_t result = other.GetInt();

    if constexpr (fraction_bits > other_fb) {
      result <<= (fraction_bits - other_fb);
    } else if constexpr (fraction_bits < other_fb) {
      result >>= (other_fb - fraction_bits);
    }

    return result;
  }

  int32_t value_;
};

#endif  // FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_