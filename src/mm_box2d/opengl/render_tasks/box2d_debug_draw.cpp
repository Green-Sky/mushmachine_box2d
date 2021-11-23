#include "./box2d_debug_draw.hpp"

#include <mm_box2d/components/world.hpp>

#include <mm/services/scene_service_interface.hpp>

#include <entt/entity/registry.hpp>

namespace MM::Box2D::OpenGL::RenderTasks {

using namespace MM::OpenGL;

void DebugDraw::render(Services::OpenGLRenderer& rs, Engine& engine) {
	MM::Scene& scene = engine.getService<MM::Services::SceneServiceInterface>().getScene();
	auto* world_ctx = scene.try_ctx<MM::Box2D::Components::World>();

	// if no b2World in scene, skip rendering
	if (!world_ctx) {
		return;
	}

	auto* debug_draw_context = scene.try_ctx<DebugDrawContext>();
	if (!debug_draw_context) {
		debug_draw_context = &_default_context;
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

	_debug_draw.SetCamera(scene.ctx<MM::OpenGL::Camera3D>());
	world_ctx->world.SetDebugDraw(&_debug_draw);
	world_ctx->world.DebugDraw();
	_debug_draw.Flush();
}

} // MM::Box2D::OpenGL::RenderTasks

