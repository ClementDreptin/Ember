#pragma once

#include <memory>

#ifndef GE_PLATFORM_WINDOWS
	#error GameEngine only supports Windows!
#endif

#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...)
	#define GE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GameEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}