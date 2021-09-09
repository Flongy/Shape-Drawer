#include <cstdint>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Shapes.h"


constexpr uint32_t INITIAL_WIDTH = 1280;
constexpr uint32_t INITIAL_HEIGHT = 720;


void setProjMatrix(double width, double height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(void)
{
	GLFWwindow* window;
	if (glfwInit() == GLFW_FALSE)
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Shape-Drawer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Could not create a window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	setProjMatrix(INITIAL_WIDTH, INITIAL_HEIGHT);

	Rect r1({ 70.0f, 120.0f });
	r1.setColor(1.0f, 0.0f, 0.0f);
	r1.setPosition({ 350.0f, 350.0f });

	Rect r2({ 150.0f, 100.0f });
	r2.setColor(0.0f, 1.0f, 0.0f);
	r2.setPosition({ 10.0f, 10.0f });

	Square s1(60.0f);
	s1.setColor(0.0f, 0.0f, 1.0f);
	s1.setPosition({50.0f, 120.0f});

	Ellipse el({ 80.0f, 50.0f });
	el.setColor(1.0f, 1.0f, 0.0f);
	el.setPosition({300.0f, 85.0f});

	Circle circle(60.0f);
	circle.setColor(1.0f, 0.0f, 1.0f);
	circle.setPosition({300.0f, 160.0f});

	Polygon poly(
	{
		{0.0f, 0.0f},
		{30.0f, 20.0f},
		{20.0f, 60.0f},
		{-20.0f, 60.0f},
		{-30.0f, 20.0f},
	});
	poly.setPosition({ 200.0f, 200.0f });

	Triangle tri1(
		{
			Vec2f{0.0f, 0.0f},
			Vec2f{120.0f, 0.0f},
			Vec2f{120.0f, 90.0f},
		}
	);
	tri1.setPosition({ 600.0f, 300.0f });

	Triangle tri2(
		{
			Vec2f{0.0f, 0.0f},
			Vec2f{50.0f, 90.0f},
			Vec2f{-50.0f, 90.0f},
		}
	);
	tri2.setPosition({ 800.0f, 300.0f });

	Triangle tri3(
		{
			Vec2f{0.0f, 0.0f},
			Vec2f{60.0f, 90.0f},
			Vec2f{150.0f, 90.0f},
		}
	);
	tri3.setPosition({ 850.0f, 300.0f });

	std::vector<Shape*> shapes{
		&r1,
		&r2,
		&s1,
		&el,
		&circle,
		&poly,
		&tri1,
		&tri2,
		&tri3,
	};

	while (!glfwWindowShouldClose(window))
	{
		/* RENDER BEGIN */
		glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto shape : shapes) {
			shape->draw();
		}

		/* RENDER END */

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}