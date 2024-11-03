#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Taro::Application* Taro::CreateApplication();

int main(int argc, char** argv) {
	Taro::Log::Init();

	TR_PROFILE_BEGIN_SESSION("Startup", "TaroProfile-Startup.json");
	auto app = Taro::CreateApplication();
	TR_PROFILE_END_SESSION();

	TR_PROFILE_BEGIN_SESSION("Runtime", "TaroProfile-Runtime.json");
	app->Run();
	TR_PROFILE_END_SESSION();

	TR_PROFILE_BEGIN_SESSION("Shutdown", "TaroProfile-Shutdown.json");
	delete app;
	TR_PROFILE_END_SESSION();
	return 0;
}

#endif

