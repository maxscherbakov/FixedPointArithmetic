#include "header/fixed_point.h"

#include <iostream>

int main() {
    int a = 12;
    int b = 123;
    FixedPoint A(128, 15);
    FixedPoint B(4, 8);
    A / B;

    std:: cout << A.value_ << std::endl;

    std:: cout << A.exp_ << '\n';

    return 0;
}