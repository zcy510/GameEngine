#include "trpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Taro {


	PerspectiveCamera::PerspectiveCamera(float aspectRatio)
		:m_ProjectionMatrix(glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f)), m_ViewMatrix(glm::lookAt(m_Position, m_Targrt, glm::vec3(0.0f, 1.0f, 0.0f)))
	{
		TR_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float zoomLevel, float aspectRatio)
	{
		TR_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::perspective(glm::radians(zoomLevel), aspectRatio, 0.1f, 100.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::UpdateDir(float xOffset, float yOffset)
	{
		m_Yaw += xOffset * 0.5f;
		m_Pitch += yOffset * 0.5f;
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_zDir = glm::normalize(front);
		m_xDir = glm::normalize(glm::cross(m_zDir, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		TR_PROFILE_FUNCTION();
		/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		m_ViewMatrix = glm::inverse(transform);*/
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_zDir, m_yDir);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}