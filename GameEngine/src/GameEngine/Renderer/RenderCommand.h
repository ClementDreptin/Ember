#pragma once

#include "RendererAPI.h"

namespace GameEngine {
	class RenderCommand {
	public:
		inline static void setClearColor(const glm::vec4& color) {
			s_RendererAPI->setClearColor(color);
		}
		
		inline static void clear() {
			s_RendererAPI->clear();
		}

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->drawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}