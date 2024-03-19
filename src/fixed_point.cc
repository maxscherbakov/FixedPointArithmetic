#include "header/fixed_point.h"

#include <cstdint>

FixedPoint::FixedPoint(int32_t value, int32_t exp) {
	value_ = value;
	exp_ = exp;
}

void FixedPoint::operator+(FixedPoint other) {
	if (exp_ >= other.exp_) {
		value_ = (value_ + other.value_ * (1 << (exp_ - other.exp_)));
	} else {
		value_ = (other.value_ + value_ * (1 << (other.exp_ - exp_)));
		exp_ = other.exp_;
	}
}

void FixedPoint::operator-() {
	value_ = -value_;
}

void FixedPoint::operator-(FixedPoint other) {
	if (exp_ >= other.exp_) {
		value_ = (value_ - other.value_ * (1 << (exp_ - other.exp_)));
	} else {
		value_ = (other.value_ - value_ * (1 << (other.exp_ - exp_)));
		exp_ = other.exp_;
	}
}

void FixedPoint::operator*(FixedPoint other) {
	value_ = value_ * other.value_;
	exp_ = exp_ + other.exp_;

}

void FixedPoint::operator/(FixedPoint other) {
	int64_t a;
	a = value_ * (1 << 16);
	value_ = (int32_t) (a / other.value_);
	exp_ = exp_ - other.exp_ + 16;
}