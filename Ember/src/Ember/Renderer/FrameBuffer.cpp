#include "ebpch.h"
#include "FrameBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Ember {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				EB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLFrameBuffer>(spec);
		}

		EB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}