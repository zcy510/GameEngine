#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Taro {
	class TARO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define TR_CORE_ERROR(...) ::Taro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TR_CORE_WARN(...) ::Taro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TR_CORE_INFO(...) ::Taro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TR_CORE_TRACE(...) ::Taro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TR_CORE_FATAL(...) ::Taro::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define TR_CLIENT_ERROR(...) ::Taro::Log::GetClientLogger()->error(__VA_ARGS__)
#define TR_CLIENT_WARN(...)	::Taro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TR_CLIENT_INFO(...)	::Taro::Log::GetClientLogger()->info(__VA_ARGS__)
#define TR_CLIENT_TRACE(...) ::Taro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TR_CLIENT_FATAL(...) ::Taro::Log::GetClientLogger()->fatal(__VA_ARGS__)

// if dist build



