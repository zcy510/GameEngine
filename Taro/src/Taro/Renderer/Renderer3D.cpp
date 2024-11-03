#include "trpch.h"
//#include "Renderer3D.h"
//#include "Renderer2D.h"
//
//namespace Taro {
//
//	Renderer3D::SceneData* Renderer3D::m_SceneData = new Renderer3D::SceneData;
//	Ref<ShaderLibrary> Renderer3D::s_ShaderLibrary = CreateRef<ShaderLibrary>();
//
//	void Renderer3D::Init()
//	{
//		s_ShaderLibrary->Load("assets/shaders/Material.glsl");
//		s_ShaderLibrary->Load("assets/shaders/MyLight.glsl");
//		s_ShaderLibrary->Load("assets/shaders/SkyBox.glsl");
//	}
//
//	void Renderer3D::Shutdown()
//	{
//		delete m_SceneData;
//	}
//
//	void Renderer3D::BeginScene(const PerspectiveCamera& camera, 
//		const Ref<DirectionalLight>& directionalLight, 
//		const std::vector<Ref<PointLight>>& pointLights, 
//		const Ref<SpotLight>& spotLight)
//	{
//		for (auto& [shaderName, shader] : Renderer3D::GetShaderLib()->GetShaders())
//		{
//			shader->Bind();
//			// camera
//			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
//			shader->SetMat4("u_View", glm::mat4(glm::mat3(camera.GetViewMatrix())));
//			shader->SetMat4("u_Projection", camera.GetProjectionMatrix());
//			shader->SetFloat3("u_ViewPosition", camera.GetPosition());
//
//			// directional light
//			if (directionalLight)
//			{
//				directionalLight->Bind(shader);
//			}
//			shader->SetInt("u_PointLightCount", pointLights.size());
//			for (int i = 0; i < pointLights.size(); ++i)
//			{
//				const auto& pointLight = pointLights[i];
//				pointLight->Bind(shader, i);
//			}
//			if (spotLight)
//			{
//				shader->SetInt("u_SpotLightCount", 1);  // TODO(islander): as an array
//				spotLight->Bind(shader);
//			}
//		}
//	}
//
//	void BeginScene(const Camera& camera)
//	{
//		for (auto& [shaderName, shader] : Renderer3D::GetShaderLib()->GetShaders())
//		{
//			shader->Bind();
//			// camera
//			shader->SetMat4("u_ViewProjection", camera.GetProjection());
//		}
//	}
//
//	void Renderer3D::EndScene()
//	{
//
//	}
//
//	void Renderer3D::Submit(const Ref<VertexArray>& vertexArray)
//	{
//		auto shader = Taro::Renderer3D::GetShaderLib()->Get("SkyBox");
//		shader->Bind();
//		shader->SetInt("skybox", 0);
//		DrawVertexArray(vertexArray);
//	}
//
//	void Renderer3D::Submit(const Mesh& mesh, const glm::mat4& modelTransform)
//	{
//		auto shader = Taro::Renderer3D::GetShaderLib()->Get("Material");
//		mesh.GetMaterial()->Bind(shader);
//		shader->SetMat4("u_Transform", modelTransform);
//		// TODO(islander): validate
//		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
//		shader->SetMat3("u_TransformNormal", modelTransformNormal);
//		
//		//RenderCommand::Draw(0, 6);
//		DrawVertexArray(mesh.GetVertexArray());
//	}
//
//	void Renderer3D::Submit(const Model& model, const glm::mat4& modelTransform)
//	{
//		
//		for (const Mesh& mesh : model.GetMeshes())
//		{
//			Submit(mesh, modelTransform);
//			
//		}
//	}
//
//	void Renderer3D::Submit(const Ref<VertexArray>& vertexArray, const Ref<Light>& light, const glm::mat4& modelTransform)
//	{
//		auto shader = Taro::Renderer3D::GetShaderLib()->Get("MyLight");
//		shader->Bind();
//		shader->SetMat4("u_Transform", modelTransform);
//		shader->SetFloat3("u_Color", light->GetColor());
//		DrawVertexArray(vertexArray);
//	}
//
//	void Renderer3D::DrawVertexArray(const Ref<VertexArray>& vertexArray)
//	{
//		vertexArray->Bind();
//
//		if (vertexArray->GetIndexBuffer())
//		{
//			RenderCommand::DrawIndexed(vertexArray, vertexArray->GetIndexBuffer()->GetCount());
//		}
//		else
//		{
//			RenderCommand::Draw(0, vertexArray->GetVertexCount());
//		}
//	}
//
//
//
//}