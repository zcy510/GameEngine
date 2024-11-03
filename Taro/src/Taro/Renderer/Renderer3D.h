//#pragma once
//#include "RenderCommand.h"
//#include "PerspectiveCamera.h"
//#include "Camera.h"
//#include "Shader.h"
//#include "Texture.h"
//#include "Material.h"
//#include "Light.h"
//#include "Mesh.h"
//#include "Model.h"
//#include "SkyBox.h"
//
//namespace Taro {
//
//	class Renderer3D
//	{
//	public:
//		static void Init();
//		static void Shutdown();
//
//		static void BeginScene(const PerspectiveCamera& camera,
//			const Ref<DirectionalLight>& directionalLight = nullptr,
//			const std::vector<Ref<PointLight>>& pointLights = {},
//			const Ref<SpotLight>& spotLight = nullptr);
//		static void EndScene();
//
//		static void Submit(const Ref<VertexArray>& vertexArray);
//
//		static void Submit(
//			const Mesh& mesh,
//			const glm::mat4& modelTransform = glm::mat4(1.0f)
//		);
//		static void Submit(
//			const Model& model,
//			const glm::mat4& modelTransform = glm::mat4(1.0f)
//		);
//		// submit a light source to draw
//		static void Submit(
//			const Ref<VertexArray>& vertexArray,
//			const Ref<Light>& light,
//			const glm::mat4& modelTransform = glm::mat4(1.0f)
//		);
//
//		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
//
//		inline static Ref<ShaderLibrary> GetShaderLib() { return s_ShaderLibrary; }
//
//	private:
//		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
//
//		// Primitives
//		// static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
//		// static void DrawCube(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture, const glm::vec4& tintcolor = glm::vec4(1.0f));
//		// static void DrawCube(const glm::vec3& position, const glm::vec3& size, std::vector<Ref<Texture2D>> textureVec, const glm::vec4& tintcolor = glm::vec4(1.0f));
//
//	private:
//		struct SceneData
//		{
//			glm::mat4 ViewProjectionMatrix;
//		};
//
//		static SceneData* m_SceneData;
//		static Ref<ShaderLibrary> s_ShaderLibrary;
//	};
//}