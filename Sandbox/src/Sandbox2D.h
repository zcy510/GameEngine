#pragma once

#include "Taro.h"
// #include "ParticleSystem.h"

class Sandbox2D :public Taro::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Taro::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Taro::Event& e) override;
private:
	Taro::OrthographicCameraController m_CameraController;

	Taro::Ref<Taro::VertexArray> m_SquareVA;
	Taro::Ref<Taro::Shader> m_FlatColorShader;

	Taro::Ref<Taro::Texture2D> m_alphaTexture;
	Taro::Ref<Taro::Texture2D> m_SpriteSheet;
	Taro::Ref<Taro::SubTexture2D> m_TextureStairs;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	std::unordered_map<char, Taro::Ref<Taro::SubTexture2D>> m_TextureMap;

	// ParticleSystem m_PaticleSystem;
};
