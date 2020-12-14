#include "ebpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ember {
	Ref<RendererAPI> RenderCommand::s_RendererAPI = CreateRef<OpenGLRendererAPI>();
}
