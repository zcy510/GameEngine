#include <Taro.h>
#include <Taro/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
#include "Sandbox3D.h"


class ExampleLayer : public Taro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Taro::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.75f, -0.75f, 0.0f, 0.8f,0.2f,0.8f,1.0f,
			0.75f, -0.75f, 0.0f, 0.2f,0.3f,0.8f,1.0f,
			0.75f, 0.75f, 0.0f, 0.8f,0.8f,0.2f,1.0f
		};

		Taro::Ref<Taro::VertexBuffer> vertexBuffer;
		vertexBuffer = Taro::VertexBuffer::Create(vertices, sizeof(vertices));

		Taro::BufferLayout layout = {
			{ Taro::ShaderDataType::Float3, "a_Position"},
			{ Taro::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Taro::Ref<Taro::IndexBuffer> indexBuffer;
		indexBuffer = Taro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Taro::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Taro::Ref<Taro::VertexBuffer> squareVB;
		squareVB = Taro::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Taro::ShaderDataType::Float3, "a_Position"},
			{ Taro::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Taro::Ref<Taro::IndexBuffer> squareIB;
		squareIB = Taro::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color=a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position, 1.0);
				color = v_Color;	
			}
  
		)";

		m_Shader = Taro::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position+0.5, 1.0);
			}

		)";

		std::string flatColorShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
  
		)";

		m_FlatColorShader = Taro::Shader::Create("FlatColor", flatColorShadervertexSrc, flatColorShaderfragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Taro::Texture2D::Create("assets/textures/Checkerboard.png");
		m_alphaTexture = Taro::Texture2D::Create("assets/textures/1.png");

		std::dynamic_pointer_cast<Taro::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Taro::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}
	
	void OnUpdate(Taro::Timestep ts) override
	{
		// Camera Update
		m_CameraController.OnUpdate(ts);

		//Renderer
		Taro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Taro::RenderCommand::Clear();

		Taro::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Taro::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Taro::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					
				Taro::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Taro::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_alphaTexture->Bind();
		Taro::Renderer::Submit(textureShader, m_SquareVA,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		// Taro::Renderer::Submit(m_Shader, m_VertexArray);

		Taro::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Taro::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Taro::ShaderLibrary m_ShaderLibrary;
	Taro::Ref<Taro::Shader> m_Shader;
	Taro::Ref<Taro::VertexArray> m_VertexArray;

	Taro::Ref<Taro::Shader> m_FlatColorShader;
	Taro::Ref<Taro::VertexArray> m_SquareVA;

	Taro::Ref<Taro::Texture2D> m_Texture, m_alphaTexture;

	Taro::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Taro::Application {
public:
	Sandbox() 
		:Application("Taro App")
	{
		//PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
		//PushLayer(new Sandbox3D());
	}

	~Sandbox()
	{

	}
};

Taro::Application* Taro::CreateApplication() {
	return new Sandbox();
}