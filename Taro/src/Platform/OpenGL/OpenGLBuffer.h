#pragma once

#include "Taro/Renderer/Buffer.h"

namespace Taro {
	class	OpenGLVertexBuffer :public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;
		virtual const BufferLayout& GetLayout() const override {return m_Layout; }

		virtual void SetLayout(const BufferLayout& layout) override 
		{
			m_Layout = layout; // To be optimized
			m_VertexCount = m_Size / layout.GetStride();
		}

		inline virtual uint32_t GetVertexCount() const override { return m_VertexCount; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
		uint32_t m_Size;
		uint32_t m_VertexCount = 0;

	};

	class	OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}