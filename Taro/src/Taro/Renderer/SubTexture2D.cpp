#include "trpch.h"
#include "SubTexture2D.h"

namespace Taro {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, glm::vec2& min, glm::vec2& max)
		:m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture)
	{
		m_Texture = texture;
	}

	void SubTexture2D::SetTexture(const std::string& filepath)
	{
		m_Texture = Texture2D::Create(filepath);
	}

	void SubTexture2D::SetTexCoords(const float width, const float height, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, float gap)
	{
		glm::vec2 min = { (coords.x * cellSize.x + coords.x * gap) / width, (coords.y * cellSize.y + coords.y * gap) / height };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x + (coords.x + spriteSize.x) * gap) / width, ((coords.y + spriteSize.y) * cellSize.y + (coords.y + spriteSize.y) * gap) / height };
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, float gap)
	{
		glm::vec2 min = { (coords.x * cellSize.x + coords.x * gap) / texture->GetWidth(), (coords.y * cellSize.y + coords.y * gap) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x + (coords.x + spriteSize.x) * gap) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y + (coords.y + spriteSize.y) * gap) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}

	Ref<SubTexture2D> SubTexture2D::Create(const Ref<Texture2D>& texture)
	{
		return CreateRef<SubTexture2D>(texture);
	}

}

