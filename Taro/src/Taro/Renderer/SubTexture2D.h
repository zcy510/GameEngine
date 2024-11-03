#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

namespace Taro {

	class SubTexture2D {

	public:
		SubTexture2D(const Ref<Texture2D>& texture, glm::vec2& min, glm::vec2& max);
		SubTexture2D(const Ref<Texture2D>& texture);
		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		void SetTexture(const std::string& filepath);
		void SetTexCoords(const float width, const float height, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 }, float gap = 0.0f);
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 }, float gap = 0.0f);
		static Ref<SubTexture2D> Create(const Ref<Texture2D>& texture);
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};
}