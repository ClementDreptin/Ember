#pragma once

namespace GameEngine {
	enum class RendererAPI {
		None = 0, OpenGL = 1, 
	};

	class Renderer {
	public:
		static inline RendererAPI getAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}