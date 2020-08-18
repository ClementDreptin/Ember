#include "gepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GameEngine {
	Ref<RendererAPI> RenderCommand::s_RendererAPI = std::make_shared<OpenGLRendererAPI>();
}