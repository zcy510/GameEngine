#include "trpch.h"
#include "OrthographicCameraController.h"

#include "Taro/Core/Input.h"
#include "Taro/Core/KeyCodes.h"

namespace Taro {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_Zoomlevel, m_AspectRatio * m_Zoomlevel, -m_Zoomlevel, m_Zoomlevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		TR_PROFILE_FUNCTION();

		//float time = ts;
		//TR_CLIENT_TRACE("Delta time: {0}s / {1}ms", ts.GetSeconds(),ts.GetMilliseconds());
		if (Input::IsKeyPressed(TR_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(TR_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(TR_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(TR_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if(m_Rotation)
		{
			if (Input::IsKeyPressed(TR_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(TR_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_Zoomlevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		TR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(TR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		CalculateView();
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_Zoomlevel, m_AspectRatio * m_Zoomlevel, -m_Zoomlevel, m_Zoomlevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		TR_PROFILE_FUNCTION();

		m_Zoomlevel -= e.GetYOffset() * 0.25f;
		m_Zoomlevel = std::max(m_Zoomlevel, 0.25f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		TR_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}