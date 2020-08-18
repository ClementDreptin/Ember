#include "gepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GameEngine {
	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}