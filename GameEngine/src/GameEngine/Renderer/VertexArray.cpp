#include "gepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GameEngine {
	VertexArray* VertexArray::create() {
		switch (Renderer::getAPI()) {
		case RendererAPI::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;	
	}
}