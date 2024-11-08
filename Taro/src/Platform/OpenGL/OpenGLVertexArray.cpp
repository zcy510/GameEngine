#include "trpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Taro {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Taro::ShaderDataType::Float: return GL_FLOAT;
		case Taro::ShaderDataType::Float2: return GL_FLOAT;
		case Taro::ShaderDataType::Float3: return GL_FLOAT;
		case Taro::ShaderDataType::Float4: return GL_FLOAT;
		case Taro::ShaderDataType::Mat3: return GL_FLOAT;
		case Taro::ShaderDataType::Mat4: return GL_FLOAT;
		case Taro::ShaderDataType::Int: return GL_INT;
		case Taro::ShaderDataType::Int2: return GL_INT;
		case Taro::ShaderDataType::Int3: return GL_INT;
		case Taro::ShaderDataType::Int4: return GL_INT;
		case Taro::ShaderDataType::Bool: return GL_BOOL;
		}

		TR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		TR_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray:: ~OpenGLVertexArray()
	{
		TR_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}


	void OpenGLVertexArray::Bind() const
	{
		TR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		if (m_IndexBuffer)
			m_IndexBuffer->Bind();
	}

	void OpenGLVertexArray::Unbind() const
	{
		TR_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		TR_PROFILE_FUNCTION();

		TR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		// uint32_t index = 0;

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}

			}

		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		TR_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	uint32_t OpenGLVertexArray::GetVertexCount() const
	{
		if (m_IndexBuffer)
		{
			return m_IndexBuffer->GetCount();
		}
		else
		{
			uint32_t elementCount = 0;
			for (const auto& vertexBuffer : m_VertexBuffers)
			{
				elementCount += vertexBuffer->GetVertexCount();
			}
			return elementCount;
		}
	}

}