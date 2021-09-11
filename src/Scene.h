#pragma once
#include <vector>
#include <memory>
#include "Shapes.h"

class Scene
{
public:
	Scene() = default;
	Scene(std::vector<std::shared_ptr<Shape>> shapes);

	void drawScene() const;
	void addShape(std::shared_ptr<Shape> shape);
	void clearScene();

private:
	std::vector<std::shared_ptr<Shape>> m_shapes{};
};

// Scene containing all shapes for test purposes
Scene makeTestScene();

// Scene filled with random shapes
Scene makeRandomScene(size_t number_of_each_shape, uint32_t screen_width, uint32_t screen_height);
