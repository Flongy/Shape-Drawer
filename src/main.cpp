#include <cstdint>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Shapes.h"
#include "Scene.h"


constexpr uint32_t INITIAL_WIDTH = 1280;
constexpr uint32_t INITIAL_HEIGHT = 720;

struct KeyStates {
	bool switchToTestScene{};
	bool switchToRandomScene{};
};


void setProjMatrix(double width, double height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	KeyStates* keyStates = (KeyStates*)glfwGetWindowUserPointer(window);

	switch (key)
	{
	case GLFW_KEY_1:
		// Switch to testScene
		if(action == GLFW_PRESS)
			keyStates->switchToTestScene = true;
		return;
	case GLFW_KEY_2:
		// Switch to randomScene
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			keyStates->switchToRandomScene = true;
		return;
	case GLFW_KEY_ESCAPE:
		// Close application on pressing ESCAPE button
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	default:
		return;
	}
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

	KeyStates keyStates{};
	glfwSetWindowUserPointer(window, &keyStates);

	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		/* RENDER BEGIN */
		glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		currentScenePtr->drawScene();
		/* RENDER END */

		if (keyStates.switchToTestScene) {
			currentScenePtr = &testScene;
			keyStates.switchToTestScene = false;
		}
		else if (keyStates.switchToRandomScene) {
			randomScene = makeRandomScene(20, INITIAL_WIDTH, INITIAL_HEIGHT);
			currentScenePtr = &randomScene;
			keyStates.switchToRandomScene = false;
		}

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}