#include <Taro.h>

class Sandbox : public Taro::Application {
public:
	Sandbox() {

	}

	~Sandbox()
	{

	}
};

Taro::Application* Taro::CreateApplication() {
	return new Sandbox();
}