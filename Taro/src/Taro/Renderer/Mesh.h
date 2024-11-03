#pragma once

#include "Taro/Core/Core.h"
#include "Vertex.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Material.h"
#include "Buffer.h"
#include "Shader.h"

namespace Taro {

	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Ref<Material>& material = nullptr);
		void Draw(const Ref<Shader>& shader);
		Mesh(Mesh&& mesh);
		Mesh& operator=(Mesh&& mesh);

		inline Ref<Material> GetMaterial() const{ return m_Material; }
		inline Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }

	private:
		void SetMesh();
		void MoveMesh(Mesh&& mesh);
	private:
		std::vector<Vertex> m_Vertices;
		std::vector< uint32_t> m_Indices;
		Ref<Material> m_Material;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}