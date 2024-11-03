#include "trpch.h"
#include "Application.h"

#include "Taro/Core/Log.h"
#include "Taro/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>


namespace Taro {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		TR_PROFILE_FUNCTION();

		TR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}

	Application::~Application() 
	{
		TR_PROFILE_FUNCTION();

	}

	void Application::PushLayer(Layer* layer)
	{
		TR_PROFILE_FUNCTION();

		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		TR_PROFILE_FUNCTION();

		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run() {
		TR_PROFILE_FUNCTION();

		while (m_Running)
		{
			TR_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();  //Platform::GetTime
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if(!m_Minimized)
			{
				{
					TR_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_layerStack)
						layer->OnUpdate(timestep);
				}
				m_ImGuiLayer->Begin();
				{
					TR_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_layerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
				/*auto [x, y] = Input::GetMousePosition();
				TR_CORE_TRACE("{0}, {1}", x, y);*/
			}

			
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		TR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		/*TR_CORE_TRACE("{0}", e);*/

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		TR_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}

