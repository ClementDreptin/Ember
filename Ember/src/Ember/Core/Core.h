#pragma once

#include <memory>

#ifndef EB_PLATFORM_WINDOWS
	#error Ember only supports Windows!
#endif

#ifdef EB_ENABLE_ASSERTS
	#define EB_ASSERT(x, ...) { if(!(x)) { EB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EB_CORE_ASSERT(x, ...) { if(!(x)) { EB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EB_ASSERT(x, ...)
	#define EB_CORE_ASSERT(x, ...)
#endif

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