#pragma once

#include "Taro/Renderer/OrthographicCamera.h"
#include "Taro/Core/Timestep.h"
#include "Taro/Events/ApplicationEvent.h"
#include "Taro/Events/MouseEvent.h"

namespace Taro {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_Zoomlevel; }
		void SetZoomLevel(float level) { m_Zoomlevel = level; CalculateView(); }
	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_Zoomlevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.1f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotationSpeed = 2.0f;
	};
}