#pragma once

#include "Taro/Renderer/PerspectiveCamera.h"
#include "Taro/Core/Timestep.h"
#include "Taro/Events/ApplicationEvent.h"
#include "Taro/Events/MouseEvent.h"

namespace Taro {

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_Zoomlevel; }
		void SetZoomLevel(float level) { m_Zoomlevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
	private:
		float m_aspectRatio;
		float m_Zoomlevel = 45.0f;
		float xLast = 640.0f;
		float yLast = 360.0f;
		bool firstMouse = true;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 2.0f };
		float m_CameraTranslationSpeed = 2.0f;
	};
}