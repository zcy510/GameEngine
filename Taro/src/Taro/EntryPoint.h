#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Taro::Application* Taro::CreateApplication();

int main(int argc, char** argv) {
	printf("Taro Engine!");
	auto app = Taro::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

