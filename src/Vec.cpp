#include "Vec.h"

Vec2f& Vec2f::operator+=(const Vec2f& right) {
	x += right.x;
	y += right.y;

	return *this;
}

Vec2f& Vec2f::operator/=(float right) {
	x /= right;
	y /= right;

	return *this;
}

Vec2f operator+(const Vec2f& left, const Vec2f& right) {
	return Vec2f{ left } += right;
}

Vec2f operator/(const Vec2f& left, float right) {
	return Vec2f{ left } /= right;
}