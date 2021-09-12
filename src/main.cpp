#include <cstdint>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Shapes.h"
#include "Scene.h"


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

	Scene testScene = makeTestScene();
	Scene randomScene = makeRandomScene(20, INITIAL_WIDTH, INITIAL_HEIGHT);
	Scene* currentScenePtr = &testScene;

	while (!glfwWindowShouldClose(window))
	{
		/* RENDER BEGIN */
		glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		currentScenePtr->drawScene();
		/* RENDER END */

		// Change the current scene with number keys
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			currentScenePtr = &testScene;
		}
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			randomScene = makeRandomScene(20, INITIAL_WIDTH, INITIAL_HEIGHT);
			currentScenePtr = &randomScene;
		}

		// Close application on pressing ESCAPE button
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}