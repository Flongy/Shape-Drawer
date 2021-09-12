#include "Scene.h"
#include <algorithm>
#include <iterator>
#include <random>


/************************/
/* Scene implementation */
/************************/
Scene::Scene(std::vector<std::shared_ptr<Shape>> shapes) : m_shapes(std::move(shapes)) {}

void Scene::drawScene() const {
	for (auto& shape : m_shapes)
		shape->draw();
}

void Scene::addShape(std::shared_ptr<Shape> shape) {
	m_shapes.push_back(shape);
}

void Scene::clearScene() {
	m_shapes.clear();
}

/********************/
/* Scene generators */
/********************/
Scene makeTestScene() {
	auto r1 = std::make_shared<Rect>(Vec2f{ 70.0f, 120.0f });
	r1->setColor(1.0f, 0.0f, 0.0f);
	r1->setPosition({ 350.0f, 350.0f });

	auto r2 = std::make_shared<Rect>(Vec2f{ 150.0f, 100.0f });
	r2->setColor(0.0f, 1.0f, 0.0f);
	r2->setPosition({ 10.0f, 10.0f });

	auto s1 = std::make_shared<Square>(60.0f);
	s1->setColor(0.0f, 0.0f, 1.0f);
	s1->setPosition({ 50.0f, 120.0f });

	auto el = std::make_shared<Ellipse>(Vec2f{ 80.0f, 50.0f });
	el->setColor(1.0f, 1.0f, 0.0f);
	el->setPosition({ 300.0f, 85.0f });

	auto circle = std::make_shared<Circle>(60.0f);
	circle->setColor(1.0f, 0.0f, 1.0f);
	circle->setPosition({ 300.0f, 160.0f });

	auto poly = std::make_shared<Polygon>(
		std::initializer_list
		{
			Vec2f{0.0f, 0.0f},
			Vec2f{30.0f, 20.0f},
			Vec2f{20.0f, 60.0f},
			Vec2f{-20.0f, 60.0f},
			Vec2f{-30.0f, 20.0f} 
		});
	poly->setPosition({ 200.0f, 200.0f });

	auto tri1 = std::make_shared<Triangle>(
			Vec2f{0.0f, 0.0f},
			Vec2f{120.0f, 0.0f},
			Vec2f{120.0f, 90.0f}
	);
	tri1->setPosition({ 600.0f, 300.0f });

	auto tri2 = std::make_shared<Triangle>(
			Vec2f{0.0f, 0.0f},
			Vec2f{50.0f, 90.0f},
			Vec2f{-50.0f, 90.0f}
	);
	tri2->setPosition({ 800.0f, 300.0f });

	auto tri3 = std::make_shared<Triangle>(
			Vec2f{0.0f, 0.0f},
			Vec2f{60.0f, 90.0f},
			Vec2f{150.0f, 90.0f}
	);
	tri3->setPosition({ 850.0f, 300.0f });

	std::vector<std::shared_ptr<Shape>> shapes{
		r1,
		r2,
		s1,
		el,
		circle,
		poly,
		tri1,
		tri2,
		tri3,
	};

	return Scene{ std::move(shapes) };
}

Scene makeRandomScene(size_t number_of_each_shape, uint32_t screen_width, uint32_t screen_height) {
	constexpr size_t VARIANTS_OF_SHAPES = 6;	// Rect, Square, Ellipse, Circle, Polygon, Triangle
	std::vector<std::shared_ptr<Shape>> shapes;
	shapes.reserve(number_of_each_shape * VARIANTS_OF_SHAPES);

	std::random_device seeder;
	auto engine = std::default_random_engine{seeder()};

	const auto width = static_cast<float>(screen_width);
	const auto height = static_cast<float>(screen_height);

	const auto uniform_size_x = std::uniform_real_distribution{ width / 20.0f, width / 10.0f };
	const auto uniform_size_y = std::uniform_real_distribution{ height / 20.0f, height / 10.0f };

	auto uniform_size_Vec2f = [uniform_size_x, uniform_size_y](auto& engine) {
		return Vec2f{ uniform_size_x(engine), uniform_size_y(engine) };
	};

#define generate(generator) std::generate_n(std::back_inserter(shapes), number_of_each_shape, generator)
	/* SHAPE GENERATORS */
	auto rect_generator = [&]() -> std::shared_ptr<Shape> {
		auto temp = std::make_shared<Rect>(uniform_size_Vec2f(engine));

		return temp;
	};
	generate(rect_generator);

	auto square_generator = [&]() -> std::shared_ptr<Shape> {
		return std::make_shared<Square>(uniform_size_y(engine));
	};
	generate(square_generator);

	auto ellipse_generator = [&]() -> std::shared_ptr<Shape> {
		return std::make_shared<Ellipse>(uniform_size_Vec2f(engine) / 2.0f);
	};
	generate(ellipse_generator);

	auto circle_generator = [&]() -> std::shared_ptr<Shape> {
		return std::make_shared<Circle>(uniform_size_y(engine) / 2.0f);
	};
	generate(circle_generator);

	auto uniform_point = [height](auto& engine) {
		auto dist = std::uniform_real_distribution{ height / -15.0f, height / 15.0f };
		return Vec2f{ dist(engine), dist(engine) };
	};

	auto polygon_generator = [&]() -> std::shared_ptr<Shape> {
		std::vector<Vec2f> points(8);

		for (auto& p : points) {
			p = uniform_point(engine);
		}

		return std::make_shared<Polygon>(std::move(points));
	};
	generate(polygon_generator);

	auto triangle_generator = [&]() -> std::shared_ptr<Shape> {
		return std::make_shared<Triangle>(
			uniform_point(engine),
			uniform_point(engine),
			uniform_point(engine)
		);
	};
	generate(triangle_generator);
#undef generate

	auto uniform_pos_x = std::uniform_real_distribution{ 0.0f, static_cast<float>(width) };
	auto uniform_pos_y = std::uniform_real_distribution{ 0.0f, static_cast<float>(height) };

	auto uniform_pos_Vec2f = [uniform_pos_x, uniform_pos_y](auto engine) {
		return Vec2f{ uniform_pos_x(engine), uniform_pos_y(engine) };
	};

	auto uniform_color = std::uniform_real_distribution{ 0.0f, 1.0f };

	for (const auto& sh : shapes) {
		sh->setPosition(uniform_pos_Vec2f(engine));
		sh->setColor(
			uniform_color(engine),
			uniform_color(engine),
			uniform_color(engine)
		);
	}

	return Scene{ std::move(shapes) };
}
