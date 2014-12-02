#include "MeshUtils.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Material.h>
#include <Graphics/Texture.h>

void MeshUtils::SetMaterial(Model* model, Material* material)
{
	for (uint32_t i = 0; i < model->m_meshParts.size(); i++)
		model->m_meshParts[i]->SetMaterial(material);
}

void MeshUtils::SetDiffusseTexture(Model* model, Texture* texture)
{
	for (uint32_t i = 0; i < model->m_meshParts.size(); i++)
	{
		Material* material = model->m_meshParts[i]->GetMaterial();
		if (material != NULL)
			material->diffuseTex = texture;
	}
}
