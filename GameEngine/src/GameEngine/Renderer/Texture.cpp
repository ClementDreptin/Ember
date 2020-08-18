#include "gepch.h"
#include "Texture.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace GameEngine {
	Ref<Texture2D> Texture2D::create(const std::string& path) {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(path);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}