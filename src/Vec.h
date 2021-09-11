#pragma once
struct Vec2f
{
	float x{};
	float y{};

	Vec2f& operator+=(const Vec2f& right);
	Vec2f& operator/=(float right);
};

Vec2f operator+(const Vec2f& left, const Vec2f& right);
Vec2f operator/(const Vec2f& left, float right);
