#pragma once

#include <memory>

#include "Ember/Core/PlatformDetection.h"

#ifdef EB_DEBUG
	#if defined(EB_PLATFORM_WINDOWS)
		#define EB_DEBUGBREAK() __debugbreak()
	#elif defined(EB_PLATFORM_LINUX)
		#include <signal.h>
		#define EB_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define EB_ENABLE_ASSERTS
#else
	#define EB_DEBUGBREAK()
#endif

#define EB_EXPAND_MACRO(x) x
#define EB_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define EB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ember {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Ember/Core/Log.h"
#include "Ember/Core/Assert.h"
