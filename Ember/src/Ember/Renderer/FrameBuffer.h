#pragma once

#include "Ember/Core/Core.h"

namespace Ember {
	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpec& GetSpec() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpec& spec);
	};
}