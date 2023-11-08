#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Taro::Application* Taro::CreateApplication();

int main(int argc, char** argv) {
	Taro::Log::Init();
	TR_CORE_WARN("Initialized Log!");
	int a = 5;
	TR_CLIENT_INFO("Hello! Var={0}", a);
	auto app = Taro::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

