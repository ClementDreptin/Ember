#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace GameEngine {
	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1,
		};

		virtual void init() = 0;

		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API getAPI() { return s_API; }
	private:
		static API s_API;
	};
}