#ifndef __tinyrender__color__
#define __tinyrender__color__

#include <cstdlib>
#include <cstdint>

class Color {

public:
	double r;
	double g;
	double b;
	double a;

	Color(double r = 1.0f, double g = 1.0f, double b = 1.0f, double a = 1.0f);
	Color(uint32_t rgba);

	static Color randomColor() {
		double r = (rand() % 255) / 255.0;
		double g = (rand() % 255) / 255.0;
		double b = (rand() % 255) / 255.0;

		Color c = Color(r, g, b, 1);
		return c;
	};

	uint32_t uint32() const;

	Color operator+(const Color & c) const {
		return Color(r + c.r, g + c.g, b + c.b, a + c.a);
	};

	Color operator-(const Color & c) const {
		return Color(r - c.r, g - c.g, b - c.b, a - c.a);
	};

	Color operator*(double factor) const {
		return Color(r * factor, g * factor, b * factor, a * factor);
	};

	Color interpolate(const Color & c, double factor) const {
		return *this + (c - *this) * factor;
	};
};

#endif
