#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	TR_PROFILE_FUNCTION();

	m_alphaTexture = Taro::Texture2D::Create("assets/textures/1.png");
	m_SpriteSheet = Taro::Texture2D::Create("assets/game/textures/tilemap_packed.png");
	//m_TextureStairs->SetTexture("assets/game/textures/tilemap_packed.png");
	m_TextureStairs = Taro::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1.0f, 1.0f }, { 18.0f, 18.0f }, { 3.0f, 3.0f }, 0.0f);
	m_CameraController.SetZoomLevel(20.0f);

	Taro::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
}

void Sandbox2D::OnDetach()
{
	TR_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Taro::Timestep ts)
{
	TR_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(ts);

	Taro::Renderer2D::ResetStats();
	{
		//Render
		TR_PROFILE_SCOPE("Renderer Prep");
		Taro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Taro::RenderCommand::Clear();
	}

	{
		TR_PROFILE_SCOPE("Renderer Draw");
		Taro::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Taro::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.5f, 1.0f });
		//Taro::Renderer2D::DrawQuad({ 0.5f, 0.0f }, { 0.5f, 0.5f }, { 0.3f, 0.2f, 0.1f, 1.0f });
		//Taro::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.5f, 5.5f }, m_SpriteSheet, 1.0f);
		Taro::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.5f, 5.5f }, m_TextureStairs, 1.0f);
		//Taro::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 2.0f,2.0f }, glm::radians(90.0f), m_alphaTexture, 1.0f, glm::vec4(0.8f, 0.3f, 0.6f, 1.0f));

		Taro::Renderer2D::EndScene();

		/*Taro::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				glm::vec4 color((x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.3f, 0.5f);
				Taro::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}

		Taro::Renderer2D::EndScene();*/
	}
	// TODO Add functions, Shader::SetMat4, Shader::SetFloat4
	// std::dynamic_pointer_cast<Taro::OpenGLShader>(m_FlatColorShader)->Bind();
	// std::dynamic_pointer_cast<Taro::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
	TR_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	auto stats = Taro::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Status: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Taro::Event& e)
{
	m_CameraController.OnEvent(e);
}
