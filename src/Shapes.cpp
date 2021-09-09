#include "Shapes.h"
#include <cmath>
#include <GLFW/glfw3.h>

constexpr float PI = 3.14159'26535'89793;
constexpr float THETA = 2 * PI;


// Base class Shape implementation
void Shape::setColor(float red, float green, float blue) {
	m_color = { red, green, blue };
}

void Shape::setPosition(float x, float y) {
	m_posX = x;
	m_posY = y;
}

void Shape::moveBy(float by_x, float by_y) {
	m_posX += by_x;
	m_posY += by_y;
}

// Rectangle implementation
Rect::Rect(float width, float height) : m_width(width), m_height(height) {}

void Rect::draw() const {
	glBegin(GL_QUADS);
	glColor3fv(m_color.data());

	glVertex2f(m_posX,				m_posY);
	glVertex2f(m_posX + m_width,	m_posY);
	glVertex2f(m_posX + m_width,	m_posY + m_height);
	glVertex2f(m_posX,				m_posY + m_height);

	glEnd();
}

// Ellipse implementation
Ellipse::Ellipse(float width, float height, size_t segments) : Rect(width, height) {
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
		glVertex2f(x * m_width + m_posX, y * m_height + m_posY);

		last_x = x;
		x = m_cosTheta * x - m_sinTheta * y;
		y = m_sinTheta * last_x + m_cosTheta * y;
	}

	glEnd();
}