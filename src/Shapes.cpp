#include "Shapes.h"
#include <cmath>
#include <GLFW/glfw3.h>

constexpr float PI = 3.14159'26535'89793;
constexpr float THETA = 2 * PI;


// Base class Shape implementation
void Shape::setColor(float red, float green, float blue) {
	m_color = { red, green, blue };
}

void Shape::setPosition(const Vec2f& position) {
	m_position = position;
}

void Shape::moveBy(const Vec2f& move_vec) {
	m_position += move_vec;
}

void Shape::setRotation(float angle_degrees) {
	m_rotation = angle_degrees;
}

const Color& Shape::getColor() const {
	return m_color;
}

const Vec2f& Shape::getPosition() const {
	return m_position;
}

float Shape::getRotation() const {
	return m_rotation;
}

// Rectangle implementation
Rect::Rect(const Vec2f& size) : m_size(size) {}

void Rect::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3fv(m_color.ptr());

	glVertex2f(0.0f, 0.0f);
	glVertex2f(m_size.x, 0.0f);
	glVertex2f(m_size.x, m_size.y);
	glVertex2f(0.0f, m_size.y);

	glEnd();
}

void Rect::setSize(const Vec2f& size) {
	m_size = size;
}

const Vec2f& Rect::getSize() const {
	return m_size;
}

// Ellipse implementation
Ellipse::Ellipse(const Vec2f& axes, size_t num_segments) : m_axes(axes) {
	setNumSegments(num_segments);
}

void Ellipse::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	float last_x{};

	float x = 1;
	float y = 0;
	

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(m_color.ptr());

	for (int i = 0; i < m_num_segments; ++i) {
		glVertex2f(x * m_axes.x, y * m_axes.y);

		last_x = x;
		x = m_cos_theta * x - m_sin_theta * y;
		y = m_sin_theta * last_x + m_cos_theta * y;
	}

	glEnd();
}

void Ellipse::setAxes(const Vec2f& axes) {
	m_axes = axes;
}

void Ellipse::setNumSegments(size_t num_segments) {
	m_num_segments = num_segments;

	const float theta_by_segments = THETA / m_num_segments;
	m_cos_theta = cosf(theta_by_segments);
	m_sin_theta = sinf(theta_by_segments);
}

const Vec2f& Ellipse::getAxes() const {
	return m_axes;
}

size_t Ellipse::getNumSegments() const {
	return m_num_segments;
}

// Polygon implementation
Polygon::Polygon(std::vector<Vec2f> points) : m_points(std::move(points)) {}

void Polygon::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(m_color.ptr());

	for (auto& point : m_points) {
		glVertex2f(point.x, point.y);
	}

	glEnd();
}

void Polygon::setPoints(std::vector<Vec2f> points) {
	m_points = std::move(points);
}

const std::vector<Vec2f>& Polygon::getPoints() const {
	return m_points;
}

std::vector<Vec2f>& Polygon::getPointsMutable() {
	return m_points;
}
