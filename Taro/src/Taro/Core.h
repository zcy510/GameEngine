#pragma once

#ifdef TR_PLATFORM_WINDOWS
	#ifdef TR_BUILD_DLL
		#define TARO_API __declspec(dllexport)
	#else 
		#define TARO_API __declspec(dllimport)
	#endif
#else
	#error Taro only supports Windows!
#endif // TR_PLATFORM_WINDOWS

