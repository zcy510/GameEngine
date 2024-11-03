//#pragma once
//
//#include "Taro.h"
//
//#include "imgui/imgui.h"
//#include "Taro/Renderer/SkyBox.h"
//#include "Taro/Renderer/Light.h"
//#include "Taro/Renderer/Renderer3D.h"
//
//class Sandbox3D : public Taro::Layer
//{
//public:
//	Sandbox3D();
//
//	virtual void OnAttach() override;
//	virtual void OnUpdate(Taro::Timestep ts) override;
//	virtual void OnDetach() override;
//
//	virtual void OnImGuiRender() override;
//
//	virtual void OnEvent(Taro::Event& e) override;
//
//private:
//	Taro::PerspectiveCameraController m_CameraController;
//
//	Taro::Ref<Taro::Model> m_Model;
//	Taro::Ref<Taro::SkyBox> m_SkyBox;
//	glm::vec3 m_ModelPos = { 0.0f, 1.0f, 0.0f };
//	float m_ModelScale = 0.2f;
//
//	Taro::Ref<Taro::DirectionalLight> m_DirectionalLight;
//	struct {
//		glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
//		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
//		float ambient = 0.1f;
//		float diffuse = 1.0f;
//		float specular = 1.0f;
//	} m_DirectionalLightProp;
//
//	std::vector<Taro::Ref<Taro::PointLight>> m_PointLights;
//	struct PointLightProps
//	{
//		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
//		glm::vec3 position = glm::vec3(-0.2f, -1.0f, -0.3f);
//		float ambient = 0.1f;
//		float diffuse = 1.0f;
//		float specular = 1.0f;
//		float constant = 1.0f;
//		float linear = 0.09f;
//		float quadratic = 0.032f;
//	};
//	std::vector<PointLightProps> m_PointLightProps;
//	Taro::Ref<Taro::VertexArray> m_PointLightVA;
//	Taro::Ref<Taro::VertexArray> m_SkyBoxVA;
//	int m_PointLightActivated = 0;
//
//	Taro::Ref<Taro::SpotLight> m_SpotLight;
//	struct {
//		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
//		float ambient = 0.1f;
//		float diffuse = 1.0f;
//		float specular = 1.0f;
//		float constant = 1.0f;
//		float linear = 0.09f;
//		float quadratic = 0.032f;
//		float cutOff = 12.5f;
//		float epsilon = 5.0f;
//	} m_SpotLightProp;
//};