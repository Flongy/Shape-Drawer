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

// Rectangle implementation
Rect::Rect(const Vec2f& size) : m_size(size) {}

void Rect::draw() const {
	glBegin(GL_QUADS);
	glColor3fv(m_color.data());

	glVertex2f(m_position.x,			m_position.y);
	glVertex2f(m_position.x + m_size.x,	m_position.y);
	glVertex2f(m_position.x + m_size.x,	m_position.y + m_size.y);
	glVertex2f(m_position.x,			m_position.y + m_size.y);

	glEnd();
}

// Ellipse implementation
Ellipse::Ellipse(const Vec2f& size, size_t segments) : Rect(size) {
	setSegments(segments);
}

void Ellipse::setSegments(size_t segments) {
	m_segments = segments;

	const float theta_by_segments = THETA / m_segments;
	m_cosTheta = cosf(theta_by_segments);
	m_sinTheta = sinf(theta_by_segments);
}

void Ellipse::draw() const {

	float last_x{};

	float x = 1;
	float y = 0;
	

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(m_color.data());

	for (int i = 0; i < m_segments; ++i) {
		glVertex2f(x * m_size.x + m_position.x, y * m_size.y + m_position.y);

		last_x = x;
		x = m_cosTheta * x - m_sinTheta * y;
		y = m_sinTheta * last_x + m_cosTheta * y;
	}

	glEnd();
}