#include "trpch.h"
#include "Mesh.h"

namespace Taro {

	
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Ref<Material>& material)
		:m_Vertices(vertices), m_Indices(indices), m_Material(material)
	{
		SetMesh();
	}

	Mesh::Mesh(Mesh&& mesh)
	{
		MoveMesh(std::move(mesh));
	}

	void Mesh::SetMesh()
	{
		m_VertexArray = VertexArray::Create();
		m_VertexBuffer = VertexBuffer::Create(reinterpret_cast<float*>(m_Vertices.data()), m_Vertices.size() * sizeof(Vertex));
		m_VertexBuffer->SetLayout(Vertex::GetLayout());
		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_VertexArray->Unbind();
	}

	void Mesh::MoveMesh(Mesh&& mesh)
	{
		m_Vertices = std::move(mesh.m_Vertices);
		m_Indices = std::move(mesh.m_Indices);
		m_Material = std::move(mesh.m_Material);

		m_VertexArray = std::move(mesh.m_VertexArray);
		m_VertexBuffer = std::move(mesh.m_VertexBuffer);
		m_IndexBuffer = std::move(mesh.m_IndexBuffer);
	}

	Mesh& Mesh::operator=(Mesh&& mesh)
	{
		MoveMesh(std::move(mesh));
		return *this;
	}
}