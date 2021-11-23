#pragma once

#include <mm/opengl/render_task.hpp>
#include <mm/services/opengl_renderer.hpp>

#include <mm/opengl/camera_3d.hpp>

#include "./draw.h"

namespace MM::Box2D::OpenGL::RenderTasks {

// contains variables determining the renderer result
struct DebugDrawContext {
	bool enable					= false;

	bool draw_aabb				= false;
	bool draw_pair				= false;
	bool draw_joint				= false;
	bool draw_center_of_mass	= false;
	bool draw_shape				= true;
};

class DebugDraw : public MM::OpenGL::RenderTask {
	private:
		::DebugDraw _debug_draw;

		// fallback, used if the scene does not provide one
		DebugDrawContext _default_context;

	public:
		explicit DebugDraw(Engine&) {}

		const char* name(void) override { return "Box2D::DebugDraw"; }

		void render(Services::OpenGLRenderer& rs, Engine& engine) override;

	public:
		std::string target_fbo = "display";
};

} // MM::Box2D::OpenGL::RenderTasks

