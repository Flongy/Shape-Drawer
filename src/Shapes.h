#pragma once
#include <vector>
#include <array>

#include "Vec.h"


class Shape
{
public:
	virtual void draw() const = 0;

	void setColor(float red, float green, float blue);
	void setPosition(const Vec2f& position);
	void moveBy(const Vec2f& move_vec);
protected:
	std::array<float, 3> m_color = { 1.0f, 1.0f, 1.0f };
	Vec2f m_position;
};

class Rect : public Shape 
{
public:
	Rect(const Vec2f& size);
	void draw() const override;
protected:
	Vec2f m_size{};
};

class Square final : public Rect 
{
public:
	Square(float side) : Rect({ side, side }) {}
};

class Ellipse : public Rect
{
public:
	Ellipse(const Vec2f& size, size_t num_segments = 24);
	void draw() const override;

	void setSegments(size_t segments);
protected:
	size_t m_segments;
	float m_cosTheta;
	float m_sinTheta;
};

class Circle final : public Ellipse
{
public:
	Circle(float radius, size_t segments = 24) : Ellipse({ radius, radius }, segments) {}
};

class Polygon : public Shape
{
public:
	Polygon(std::vector<Vec2f> points);
	void draw() const override;

protected:
	std::vector<Vec2f> m_points;
};

class Triangle final : public Polygon
{
public:
	Triangle(std::array<Vec2f, 3> points) : Polygon({ points.begin(), points.end() }) {}
};
