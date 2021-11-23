#pragma once

#include <box2d/b2_world.h>

namespace MM::Box2D::Components {

struct World {
	b2World world{{0.f, 0.f}};

	int32_t velocity_iterations = 6; // 8
	int32_t position_iterations = 2; // 4
};

} // MM::Box2D::Components

