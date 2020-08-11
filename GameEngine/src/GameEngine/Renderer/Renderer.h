#pragma once

#include "RenderCommand.h"

namespace GameEngine {
	class Renderer {
	public:
		static void beginScene();
		static void endScene();

		static void submit(const std::shared_ptr<VertexArray> vertexArray);

		static inline RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	};
}