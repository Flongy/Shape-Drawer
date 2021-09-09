#include "Vec.h"

Vec2f& Vec2f::operator+=(const Vec2f& right) {
	x += right.x;
	y += right.y;

	return *this;
}

Vec2f operator+(const Vec2f& left, const Vec2f& right) {
	return { left.x + right.x, left.x + right.x };
}