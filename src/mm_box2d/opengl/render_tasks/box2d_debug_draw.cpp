#include "./box2d_debug_draw.hpp"

#include <mm_box2d/components/world.hpp>

#include <mm/services/scene_service_interface.hpp>

#include <entt/entity/registry.hpp>

namespace MM::Box2D::OpenGL::RenderTasks {

using namespace MM::OpenGL;

void DebugDraw::render(Services::OpenGLRenderer& rs, Engine& engine) {
	auto* ssi = engine.tryService<MM::Services::SceneServiceInterface>();
	if (ssi == nullptr) {
		return; // nothing to draw
	}

	auto& scene = ssi->getScene();

	if (!scene.ctx().contains<Camera3D>()) {
		return; // nothing to draw
	}

	if (!scene.ctx().contains<MM::Box2D::Components::World>()) {
		return; // nothing to draw
	}

	auto& world_ctx = scene.ctx().get<MM::Box2D::Components::World>();

	DebugDrawContext* debug_draw_context = &_default_context;
	if (scene.ctx().contains<DebugDrawContext>()) {
		debug_draw_context = &scene.ctx().get<DebugDrawContext>();
	}

	if (!debug_draw_context->enable) {
		return; // disabled, early out
	}

	rs.targets[target_fbo]->bind(FrameBufferObject::W);

	glDisable(GL_DEPTH_TEST);

	uint32_t flags =
		(debug_draw_context->draw_aabb ? b2Draw::e_aabbBit : 0) |
		(debug_draw_context->draw_pair ? b2Draw::e_pairBit : 0) |
		(debug_draw_context->draw_joint ? b2Draw::e_jointBit : 0) |
		(debug_draw_context->draw_center_of_mass ? b2Draw::e_centerOfMassBit : 0) |
		(debug_draw_context->draw_shape ? b2Draw::e_shapeBit : 0);

	_debug_draw.SetFlags(flags);

	_debug_draw.SetCamera(scene.ctx().get<MM::OpenGL::Camera3D>());
	world_ctx.world.SetDebugDraw(&_debug_draw);
	world_ctx.world.DebugDraw();
	_debug_draw.Flush();
}

} // MM::Box2D::OpenGL::RenderTasks

