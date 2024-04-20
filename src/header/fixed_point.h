#ifndef FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_
#define FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_


template<uint8_t fraction_bits=16, typename TypeValue=int32_t>
class FixedPoint {
 public:
  FixedPoint(float value) {
    value_ = (TypeValue)(std::round((double)value * (1 << fraction_bits)));
  }

  float GetFloat() {
    return (value_ >> fraction_bits) + 
    (float)(value_ % (1 << fraction_bits)) / (1 << fraction_bits);
  }

  TypeValue GetInt() const {
    return value_;
  }


  template<uint8_t other_fb, typename otherType>
  void operator+=(const FixedPoint<other_fb, otherType>& other) {
    value_= (TypeValue)(value_ + ValueConversion(other));
  }


  template<uint8_t other_fb, typename otherType>
  FixedPoint operator+(const FixedPoint<other_fb, otherType>& other) {
    FixedPoint<fraction_bits, TypeValue> result = *this;
    result += other;

    return result;
  }


  template<uint8_t other_fb, typename otherType>
  void operator-=(const FixedPoint<other_fb, otherType>& other) {
    value_= (TypeValue)((int64_t)value_ - ValueConversion(other));
  }
  
  FixedPoint operator-() {
    FixedPoint<fraction_bits, TypeValue> result = *this;
    result.value_ = -result.value_;
    
    return result;
  }

  template<uint8_t other_fb, typename otherType>
  FixedPoint operator-(const FixedPoint<other_fb, otherType>& other) {
    FixedPoint<fraction_bits, TypeValue> result = *this;
    result -= other;

    return result;
  }

  template<uint8_t other_fb, typename otherType>
  void operator*=(const FixedPoint<other_fb, otherType>& other) {
    value_ = (TypeValue)((int64_t)value_ * other.GetInt() >> other_fb);
  }


  template<uint8_t other_fb, typename otherType>
  FixedPoint operator*(const FixedPoint<other_fb, otherType>& other) {
	
    FixedPoint<fraction_bits, TypeValue> result = *this;
    result *= other;
	

    return result;
  }

  template<uint8_t other_fb, typename otherType>
  void operator/=(const FixedPoint<other_fb, otherType>& other) {
    value_ = (TypeValue)(((int64_t)value_ << other_fb) / other.GetInt());
  }

  template<uint8_t other_fb, typename otherType>
  FixedPoint operator/(const FixedPoint<other_fb, otherType>& other) {
    FixedPoint<fraction_bits, TypeValue> result = *this;
    result /= other;

    return result;
  }

 private:
  template<uint8_t other_fb, typename otherType>
  constexpr TypeValue ValueConversion(const FixedPoint<other_fb, otherType>& other) {
    TypeValue result = (TypeValue)other.GetInt();

    if constexpr (fraction_bits > other_fb) {
      result <<= (fraction_bits - other_fb);
    } else if constexpr (fraction_bits < other_fb) {
      result >>= (other_fb - fraction_bits);
    }

    return result;
  }

  TypeValue value_;
};

#endif  // FIXEDPOINTARITHMETIC_HEADER_FIXED_POINT_H_