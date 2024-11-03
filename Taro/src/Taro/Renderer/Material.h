#pragma once
#include "Taro/Core/Core.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Taro {

	// To be optimized
	class Material
	{
	public:
		Material(
			Ref<Texture2D> diffuseMap = nullptr,
			Ref<Texture2D> specularMap = nullptr,
			Ref<Texture2D> emissionMap = nullptr,
			float shininess = 32.0f
		);
		
		inline void SetDiffuseMap(Ref<Texture2D> texture) { m_DiffuseMap = texture; }
		inline void SetSpecularMap(Ref<Texture2D> texture) { m_SpecularMap = texture; }
		inline void SetEmissionMap(Ref<Texture2D> texture) { m_EmissionMap = texture; }
		inline float GetShininess() const { return m_Shininess; }
		inline void SetShininess(float shininess) { m_Shininess = shininess; }

		void Bind(const Ref<Shader>& shader);
		void SetTextureMap(Ref<Texture2D> texture, Texture::Type type);


	private:
		static const uint32_t m_DiffuseSlot = 0;
		static const uint32_t m_SpecularSlot = 1;
		static const uint32_t m_EmissionSlot = 2;
		Ref<Texture2D> m_DiffuseMap;
		Ref<Texture2D> m_SpecularMap;
		Ref<Texture2D> m_EmissionMap;
		float m_Shininess;
	};
}