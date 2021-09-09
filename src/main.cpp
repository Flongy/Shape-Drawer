#include <cstdint>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Shapes.h"


constexpr uint32_t INITIAL_WIDTH = 640;
constexpr uint32_t INITIAL_HEIGHT = 480;


int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Shape-Drawer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Could not create a window\n";
		glfwTerminate();
		return -1;
	}

	// Window resizing
	glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height) {
		glPushMatrix();
		glOrtho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height), -1.0, 1.0);
		glPopMatrix();
	});

	glfwMakeContextCurrent(window);

	glOrtho
	(
		0.0, 
		static_cast<double>(INITIAL_WIDTH), 
		0.0, 
		static_cast<double>(INITIAL_HEIGHT), 
		-1.0, 
		1.0
	);

	Rect r1(20.0f, 20.0f);
	r1.setColor(1.0f, 0.0f, 0.0f);
	r1.setPosition(350.0f, 350.0f);

	Rect r2(150.0f, 100.0f);
	r2.setColor(0.0f, 1.0f, 0.0f);
	r2.setPosition(10.0f, 10.0f);

	Square s1(60.0f);
	s1.setColor(0.0f, 0.0f, 1.0f);
	s1.setPosition(50.0f, 120.0f);

	Ellipse el(80.0f, 50.0f);
	el.setColor(1.0f, 1.0f, 0.0f);
	el.setPosition(300.0f, 85.0f);

	Circle circle(60.0f);
	circle.setColor(1.0f, 0.0f, 1.0f);
	circle.setPosition(300.0f, 160.0f);

	std::vector<Shape*> shapes{
		&r1,
		&r2,
		&s1,
		&el,
		&circle
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