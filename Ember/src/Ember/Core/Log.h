#pragma once

#include "Core.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Ember {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define EB_CORE_TRACE(...) ::Ember::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EB_CORE_INFO(...) ::Ember::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EB_CORE_WARN(...) ::Ember::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EB_CORE_ERROR(...) ::Ember::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EB_CORE_FATAL(...) ::Ember::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EB_TRACE(...) ::Ember::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EB_INFO(...) ::Ember::Log::GetClientLogger()->info(__VA_ARGS__)
#define EB_WARN(...) ::Ember::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EB_ERROR(...) ::Ember::Log::GetClientLogger()->error(__VA_ARGS__)
#define EB_FATAL(...) ::Ember::Log::GetClientLogger()->critical(__VA_ARGS__)
