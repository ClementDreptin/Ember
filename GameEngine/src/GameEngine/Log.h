#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace GameEngine {
	class GE_API Log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GE_CORE_TRACE(...) ::GameEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...) ::GameEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...) ::GameEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...) ::GameEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_FATAL(...) ::GameEngine::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define GE_TRACE(...) ::GameEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...) ::GameEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...) ::GameEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...) ::GameEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define GE_FATAL(...) ::GameEngine::Log::getClientLogger()->fatal(__VA_ARGS__)