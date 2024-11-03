#pragma once
#include "Taro/Core/Core.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Taro {

	class SkyBox {
	public:
		SkyBox() = delete;
		SkyBox(const std::string& path) { LoadSkyBox(path); }
	private:
		uint32_t m_RendererID;
		std::vector<std::string> m_Faces;
	private:
		void LoadSkyBox(const std::string& path);
	};
}