#include "trpch.h"
#include "PerspectiveCameraController.h"

#include "Taro/Core/Input.h"
#include "Taro/Core/KeyCodes.h"
#include "Taro/Core/MouseButtonCodes.h"

namespace Taro {


	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio)
		:m_aspectRatio(aspectRatio), m_Camera(m_aspectRatio)
	{

	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		TR_PROFILE_FUNCTION();

		//float time = ts;
		//TR_CLIENT_TRACE("Delta time: {0}s / {1}ms", ts.GetSeconds(),ts.GetMilliseconds());
		if (Input::IsKeyPressed(TR_KEY_A))
			m_CameraPosition -= (float)ts * m_Camera.GetxDir() * m_CameraTranslationSpeed;
		else if (Input::IsKeyPressed(TR_KEY_D))
			m_CameraPosition += (float)ts * m_Camera.GetxDir() * m_CameraTranslationSpeed;

		if (Input::IsKeyPressed(TR_KEY_W))
			m_CameraPosition += (float)ts * m_Camera.GetzDir() * m_CameraTranslationSpeed;
		else if (Input::IsKeyPressed(TR_KEY_S))
			m_CameraPosition -= (float)ts * m_Camera.GetzDir() * m_CameraTranslationSpeed;

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_Zoomlevel * 0.1f;
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		TR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(TR_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(TR_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		TR_PROFILE_FUNCTION();

		m_Zoomlevel -= e.GetYOffset();
		m_Zoomlevel = std::max(m_Zoomlevel, 1.0f);
		m_Zoomlevel = std::min(m_Zoomlevel, 179.0f);
		m_Camera.SetProjection(m_Zoomlevel, m_aspectRatio);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		TR_PROFILE_FUNCTION();

		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_Zoomlevel, m_aspectRatio);
		return false;
	}

	// TODO: Camera viewport rotate
	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		TR_PROFILE_FUNCTION();

		if (Input::IsMouseButtonPressed(TR_MOUSE_BUTTON_LEFT))
		{
			if (firstMouse)
			{
				xLast = e.GetX();
				yLast = e.GetY();
				firstMouse = false;
			}

			float xOffset = e.GetX() - xLast;
			float yOffset = yLast - e.GetY();
			xLast = e.GetX();
			yLast = e.GetY();

			m_Camera.UpdateDir(xOffset, yOffset);
		}
		else
		{
			firstMouse = true;
		}
		return false;
	}

}