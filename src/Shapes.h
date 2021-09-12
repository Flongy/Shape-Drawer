#pragma once
#include <vector>
#include <array>

#include "Vec.h"


struct Color {
	float red{};
	float green{};
	float blue{};

	const float* ptr() const { return reinterpret_cast<const float*>(this); }
};

class Shape
{
public:
	virtual void draw() const = 0;

	void setColor(Color color);
	void setPosition(Vec2f position);
	void moveBy(Vec2f move_vec);
	void setRotation(float angle_degrees);

	Color getColor() const;
	Vec2f getPosition() const;
	float getRotation() const;
protected:
	Color m_color = { 1.0f, 1.0f, 1.0f };
	Vec2f m_position;
	float m_rotation{};
};

class Rect : public Shape 
{
public:
	Rect(Vec2f size = { 50.0f, 20.0f });
	void draw() const override;

	void setSize(Vec2f size);
	Vec2f getSize() const;
protected:
	Vec2f m_size;
};

class Square final : public Rect 
{
public:
	Square(float side = 30.0f) : Rect({ side, side }) {}

	void setSize(float side) { Rect::setSize({ side, side }); }
	float getSize() const { return m_size.x; }
};

class Ellipse : public Shape
{
public:
	Ellipse(Vec2f axes = { 20.0f, 10.0f }, size_t num_segments = 24);
	void draw() const override;

	void setAxes(Vec2f axes);
	void setNumSegments(size_t num_segments);

	Vec2f getAxes() const;
	size_t getNumSegments() const;
protected:
	Vec2f m_axes;			// { vertical semi-axis, horizontal semi-axis }
	size_t m_num_segments;
	float m_cos_theta;
	float m_sin_theta;
};

class Circle final : public Ellipse
{
public:
	Circle(float radius = 30.0f, size_t num_segments = 24) : Ellipse({ radius, radius }, num_segments) {}

	void setAxes(float radius) { Ellipse::setAxes({ radius, radius }); }
	float getAxes() const { return m_axes.x; }
};

class Polygon : public Shape
{
public:
	Polygon() = default;
	Polygon(std::vector<Vec2f> points);
	void draw() const override;

	void setPoints(std::vector<Vec2f> points);
	const std::vector<Vec2f>& getPoints() const;
	std::vector<Vec2f>& getPointsMutable();

protected:
	std::vector<Vec2f> m_points{
		{0.0f, 0.0f},
		{30.0f, 20.0f},
		{20.0f, 60.0f},
		{-20.0f, 60.0f},
		{-30.0f, 20.0f}
	};
};

class Triangle final : public Polygon
{
public:
	Triangle(Vec2f point1 = { 0.0f, 0.0f }, 
			 Vec2f point2 = { 10.0f, 30.0f }, 
			 Vec2f point3 = { -10.0f, 30.0f }) : Polygon({ point1, point2, point3 }) {}
};
