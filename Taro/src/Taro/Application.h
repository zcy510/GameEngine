#pragma once

#include "Core.h"

namespace Taro {
	class TARO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}


