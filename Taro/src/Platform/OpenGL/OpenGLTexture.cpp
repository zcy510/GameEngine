#include "trpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

namespace Taro {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
		:m_Path(""), m_Width(width), m_Height(height), m_Channels(4)
	{
		TR_PROFILE_FUNCTION();

		Init();
		if (data)
		{
			SetData(data, m_Width * m_Height * m_Channels);
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		TR_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			TR_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		TR_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		Init();

		SetData(data, m_Width * m_Height * m_Channels);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		TR_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		TR_PROFILE_FUNCTION();

		// uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		TR_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		TR_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::Init()
	{
		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		TR_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

}