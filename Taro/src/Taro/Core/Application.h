#pragma once

#include "Core.h"
#include "Window.h"
#include "Taro/Core/LayerStack.h"
#include "Taro/Events/Event.h"
#include "Taro/Events/ApplicationEvent.h"

#include "Taro/Core/Timestep.h"

#include "Taro/ImGui/ImGuiLayer.h"

namespace Taro {
	class TARO_API Application
	{
	public:
		Application(const std::string& name = "TaroEditor");
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_layerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}