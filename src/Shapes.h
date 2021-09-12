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

class Ellipse : public Shape
{
public:
	Ellipse(const Vec2f& size, size_t num_segments = 24);
	void draw() const override;

	void setSegments(size_t num_segments);
protected:
	Vec2f m_axes;			// { vertical semi-axis, horizontal semi-axis }
	size_t m_num_segments;
	float m_cos_theta;
	float m_sin_theta;
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
	Triangle(Vec2f point1 = { 0.0f, 0.0f }, 
			 Vec2f point2 = { 10.0f, 30.0f }, 
			 Vec2f point3 = { -10.0f, 30.0f }) : Polygon({ point1, point2, point3 }) {}
};
