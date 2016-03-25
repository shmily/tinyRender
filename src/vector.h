#ifndef __tinyrender__vector__
#define __tinyrender__vector__

#include "rmath.h"

class Vector {

public:
	double x;
	double y;
	double z;

	Vector(double x = 0.0f, double y = 0.0f, double z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	double length() const;
	Vector normalize() const;

	double dot(const Vector & v) const;
	Vector cross(const Vector & v) const;
	Vector interpolate(const Vector & v, double factor) const;

	Vector operator+(const Vector & v) const {
		return Vector(x + v.x, y + v.y, z + v.z);
	};

	Vector operator-(const Vector & v)const {
		return Vector(x - v.x, y - v.y, z - v.z);
	};

	Vector operator*(double factor)const {
		return Vector(x * factor, y * factor, z * factor);
	};

	bool operator==(const Vector & v)const {
		return double_equal(x, v.x) && double_equal(y, v.y)
		    && double_equal(z, v.z);
	};
};

#endif
