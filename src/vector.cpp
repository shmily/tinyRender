#include "vector.h"

double
Vector::length() const {
	return sqrt(x * x + y * y + z * z);
}

Vector
Vector::normalize() const {
	double factor = 0.;
	double length = this->length();

	if (length > 0.) {
		factor = 1. / length;
	}

	return Vector(x * factor, y * factor, z * factor);
};

double
Vector::dot(const Vector & v) const {
	return x * v.x + y * v.y + z * v.z;
};

Vector
Vector::cross(const Vector & v) const {
	double X = y * v.z - z * v.y;
	double Y = z * v.x - x * v.z;
	double Z = x * v.y - y * v.x;
	return Vector(X, Y, Z);
};

Vector
Vector::interpolate(const Vector & v, double factor) const
{
	return *this + (v - *this) * factor;
};
