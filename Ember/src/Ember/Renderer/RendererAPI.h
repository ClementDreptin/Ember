#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Ember {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}
