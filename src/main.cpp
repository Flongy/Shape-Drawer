#include <cstdint>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "Shapes.h"
#include "Scene.h"

#include "MemoryCheck.h"


constexpr uint32_t INITIAL_WIDTH = 1280;
constexpr uint32_t INITIAL_HEIGHT = 720;

struct KeyStates {
	bool switch_to_test_scene{};
	bool switch_to_random_scene{};
	bool increase_shape_num_in_random_scene{};
	bool decrease_shape_num_in_random_scene{};
};


void setProjMatrix(double width, double height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	KeyStates* key_states = (KeyStates*)glfwGetWindowUserPointer(window);

	switch (key)
	{
	case GLFW_KEY_1:
		// Switch to testScene
		if(action == GLFW_PRESS)
			key_states->switch_to_test_scene = true;
		return;
	case GLFW_KEY_2:
		// Switch to randomScene
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			key_states->switch_to_random_scene = true;
		return;
	case GLFW_KEY_EQUAL:
	case GLFW_KEY_KP_ADD:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			key_states->increase_shape_num_in_random_scene = true;
		return;
	case GLFW_KEY_MINUS:
	case GLFW_KEY_KP_SUBTRACT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			key_states->decrease_shape_num_in_random_scene = true;
		return;
	case GLFW_KEY_ESCAPE:
		// Close application on pressing ESCAPE button
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	case GLFW_KEY_M:
		if(action == GLFW_PRESS)
			printMemoryUsage();
		return;
	default:
		return;
	}
}


int main()
{
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

		constexpr size_t MINIMUM_SHAPE_NUM = 20;
		constexpr size_t MAXIMUM_SHAPE_NUM = 1'000;
		constexpr size_t CHANGE_SHAPE_NUM_STEP = 10;
		int32_t random_scene_each_shape_num = MINIMUM_SHAPE_NUM;

		Scene test_scene = makeTestScene();
		Scene random_scene = makeRandomScene(random_scene_each_shape_num, INITIAL_WIDTH, INITIAL_HEIGHT);
		Scene* current_scene_ptr = &test_scene;

		KeyStates key_states{};
		glfwSetWindowUserPointer(window, &key_states);

		glfwSetKeyCallback(window, keyCallback);

		while (!glfwWindowShouldClose(window))
		{
			/* RENDER BEGIN */
			glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			current_scene_ptr->drawScene();
			/* RENDER END */

			if (key_states.switch_to_test_scene) {
				current_scene_ptr = &test_scene;
				key_states.switch_to_test_scene = false;
			}
			else if (key_states.switch_to_random_scene) {
				random_scene = makeRandomScene(random_scene_each_shape_num, INITIAL_WIDTH, INITIAL_HEIGHT);
				current_scene_ptr = &random_scene;
				key_states.switch_to_random_scene = false;
			}

			if (key_states.increase_shape_num_in_random_scene) {
				random_scene_each_shape_num += CHANGE_SHAPE_NUM_STEP;

				if (random_scene_each_shape_num > MAXIMUM_SHAPE_NUM) {
					random_scene_each_shape_num = MAXIMUM_SHAPE_NUM;
				}
				else if (current_scene_ptr == &random_scene) {
					// if the random scene is currently selected - reinitialize it
					// otherwise - postpone creating until scene is requested
					random_scene = makeRandomScene(random_scene_each_shape_num, INITIAL_WIDTH, INITIAL_HEIGHT);
				}

				key_states.increase_shape_num_in_random_scene = false;
			}
			else if (key_states.decrease_shape_num_in_random_scene) {
				random_scene_each_shape_num -= CHANGE_SHAPE_NUM_STEP;

				if (random_scene_each_shape_num < MINIMUM_SHAPE_NUM) {
					random_scene_each_shape_num = MINIMUM_SHAPE_NUM;
				}
				else if (current_scene_ptr == &random_scene) {
					// if the random scene is currently selected - reinitialize it
					// otherwise - postpone creating until scene is requested
					random_scene = makeRandomScene(random_scene_each_shape_num, INITIAL_WIDTH, INITIAL_HEIGHT);
				}

				key_states.decrease_shape_num_in_random_scene = false;
			}

			glfwSwapBuffers(window);

			glfwPollEvents();
		}

		glfwTerminate();
	}

	std::cout << "Memory used in the end:\n";
	printMemoryUsage();
	std::cin.get();
	return 0;
}
