#include "trpch.h"
#include "SkyBox.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Taro {

	void SkyBox::LoadSkyBox(const std::string& path)
	{
		m_Faces = std::vector<std::string>
		{
			path + "/right.jpg", path + "/left.jpg",
			path + "/top.jpg", path + "/bottom.jpg",
			path + "/front.jpg", path + "/back.jpg"
		};
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		int width, height, channels;
		for (unsigned int i = 0; i < 6; i++)
		{
			stbi_set_flip_vertically_on_load(false);
			unsigned char* data = stbi_load(m_Faces[i].c_str(), &width, &height, &channels, 0);
			stbi_set_flip_vertically_on_load(true);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				TR_CORE_ERROR("Cubemap texture failed to load at path: {0}", m_Faces[i]);
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

}

