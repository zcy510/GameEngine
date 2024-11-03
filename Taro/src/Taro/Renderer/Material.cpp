#include "trpch.h"
#include "Material.h"

namespace Taro {


	Material::Material(Ref<Texture2D> diffuseMap, Ref<Texture2D> specularMap, Ref<Texture2D> emissionMap, float shininess)
		:m_Shininess(shininess)
	{
		auto blackTexture = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_DiffuseMap = (diffuseMap) ? diffuseMap : blackTexture;
		m_SpecularMap = (specularMap) ? specularMap : blackTexture;
		m_EmissionMap = (emissionMap) ? emissionMap : blackTexture;
	}

	void Material::Bind(const Ref<Shader>& shader)
	{
		shader->Bind();

		// diffuse
		TR_CORE_ASSERT(m_DiffuseMap, "Material has no diffuse map!");
		m_DiffuseMap->Bind(m_DiffuseSlot);
		shader->SetInt("u_Material.diffuse", m_DiffuseSlot);
		// specular
		m_SpecularMap->Bind(m_SpecularSlot);
		shader->SetInt("u_Material.specular", m_SpecularSlot);
		shader->SetFloat("u_Material.shininess", m_Shininess);
		// emission
		m_EmissionMap->Bind(m_EmissionSlot);
		shader->SetInt("u_Material.emission", m_EmissionSlot);

		m_DiffuseMap->Bind(m_DiffuseSlot);
	}

	void Material::SetTextureMap(Ref<Texture2D> texture, Texture::Type type)
	{
		switch (type)
		{
		case Texture::Type::Diffuse:
			SetDiffuseMap(texture);
			break;
		case Texture::Type::Specular:
			SetSpecularMap(texture);
			break;
		case Texture::Type::Emission:
			SetEmissionMap(texture);
			break;
		default:
			TR_CORE_ASSERT(false, "Unknown texture type!");
		}
	}

}