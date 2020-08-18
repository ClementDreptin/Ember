#include "gepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {
	Ref<VertexArray> VertexArray::create() {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;	
	}
}