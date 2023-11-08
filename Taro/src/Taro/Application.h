#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Taro/Events/ApplicationEvent.h"
#include "Window.h"
#include "Taro/LayerStack.h"

#include "Taro/ImGui/ImGuiLayer.h"

namespace Taro {
	class TARO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_layerStack;

		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}



