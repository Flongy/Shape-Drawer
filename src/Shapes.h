#pragma once
#include <array>

class Shape
{
public:
	virtual void draw() const = 0;

	void setColor(float red, float green, float blue);
	void setPosition(float x, float y);
	void moveBy(float by_x, float by_y);
protected:
	std::array<float, 3> m_color = { 1.0f, 1.0f, 1.0f };
	float m_posX{};
	float m_posY{};
};

class Rect : public Shape 
{
public:
	Rect(float width, float height);
	void draw() const override;
protected:
	float m_width{};
	float m_height{};
};

class Square final : public Rect 
{
public:
	Square(float side) : Rect(side, side) {}
};

class Ellipse : public Rect
{
public:
	Ellipse(float width, float height, size_t num_segments = 24);
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
	Circle(float radius, size_t segments = 24) : Ellipse(radius, radius, segments) {}
};
