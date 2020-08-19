#include "gepch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GameEngine {
	Ref<Shader> Shader::create(const std::string& path) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(path);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}