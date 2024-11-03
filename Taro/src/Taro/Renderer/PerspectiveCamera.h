#pragma once

#include <glm/glm.hpp>

namespace Taro {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float aspectRatio);
		void SetProjection(float zoomLevel, float aspectRatio);
		void UpdateDir(float xOffset, float yOffset);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		const glm::vec3& GetxDir() const { return m_xDir; }
		const glm::vec3& GetyDir() const { return m_yDir; }
		const glm::vec3& GetzDir() const { return m_zDir; }

	private:
		void RecalculateViewMatrix();

	private:
		float m_aspectRatio = 1280.f / 720.0f;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.1f };
		glm::vec3 m_Targrt = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_xDir = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_zDir = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_yDir = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}