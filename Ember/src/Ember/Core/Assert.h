#pragma once

#include "Ember/Core/Core.h"
#include "Ember/Core/Log.h"
#include <filesystem>

#ifdef EB_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define EB_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EB##type##ERROR(msg, __VA_ARGS__); EB_DEBUGBREAK(); } }
	#define EB_INTERNAL_ASSERT_WITH_MSG(type, check, ...) EB_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define EB_INTERNAL_ASSERT_NO_MSG(type, check) EB_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EB_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define EB_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define EB_INTERNAL_ASSERT_GET_MACRO(...) EB_EXPAND_MACRO( EB_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EB_INTERNAL_ASSERT_WITH_MSG, EB_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define EB_ASSERT(...) EB_EXPAND_MACRO( EB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define EB_CORE_ASSERT(...) EB_EXPAND_MACRO( EB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define EB_ASSERT(...)
	#define EB_CORE_ASSERT(...)
#endif
