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

// Rectangle implementation
Rect::Rect(const Vec2f& size) : m_size(size) {}

void Rect::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	glColor3fv(m_color.data());

	/*glVertex2f(m_position.x,			m_position.y);
	glVertex2f(m_position.x + m_size.x,	m_position.y);
	glVertex2f(m_position.x + m_size.x,	m_position.y + m_size.y);
	glVertex2f(m_position.x,			m_position.y + m_size.y);*/

	glVertex2f(0.0f, 0.0f);
	glVertex2f(m_size.x, 0.0f);
	glVertex2f(m_size.x, m_size.y);
	glVertex2f(0.0f, m_size.y);

	glEnd();
}

// Ellipse implementation
Ellipse::Ellipse(const Vec2f& axes, size_t num_segments) : m_axes(axes) {
	setSegments(num_segments);
}

void Ellipse::setSegments(size_t num_segments) {
	m_num_segments = num_segments;

	const float theta_by_segments = THETA / m_num_segments;
	m_cos_theta = cosf(theta_by_segments);
	m_sin_theta = sinf(theta_by_segments);
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
	glColor3fv(m_color.data());

	for (int i = 0; i < m_num_segments; ++i) {
		glVertex2f(x * m_axes.x, y * m_axes.y);

		last_x = x;
		x = m_cos_theta * x - m_sin_theta * y;
		y = m_sin_theta * last_x + m_cos_theta * y;
	}

	glEnd();
}

// Polygon implementation
Polygon::Polygon(std::vector<Vec2f> points) : m_points(std::move(points)) {}

void Polygon::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3fv(m_color.data());

	for (auto& point : m_points) {
		glVertex2f(point.x, point.y);
	}

	glEnd();
}
