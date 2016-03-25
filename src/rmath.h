#ifndef __tinyrender__math__
#define __tinyrender__math__

#include <cmath>

const double _double_epsilon = 0.0001;
const double PI = 3.1415926535;

static inline bool
double_equal(double a, double b) {
    return fabs(a - b) <= _double_epsilon;
}

static inline double
radians_from_degrees(double degrees) {
    return PI * degrees / 180.0f;
}

static inline double
degrees_from_radians(double radians) {
    return 180.0f * radians / PI;
}

#endif
