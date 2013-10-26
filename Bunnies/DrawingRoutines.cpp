#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/Content/Content.h>
#include <Graphics/Shader.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Mesh.h>
#include <Graphics/Material.h>
#include <Graphics/Model.h>
#include <Graphics/OpenglPort.h>
#include <assert.h>

Shader* DrawingRoutines::m_celShadingShader;
Shader* DrawingRoutines::m_celShadingMutatingShader;
Shader* DrawingRoutines::m_outlineShader;
Shader* DrawingRoutines::m_outlineMutatingShader;
Shader* DrawingRoutines::m_skydomeShader;
Shader* DrawingRoutines::m_diffTexShader;
Shader* DrawingRoutines::m_diffShader;
Shader* DrawingRoutines::m_grassShader;
float DrawingRoutines::m_outlineWidth;
sm::Vec3 DrawingRoutines::m_lightPosition;
sm::Vec3 DrawingRoutines::m_eyePosition;
sm::Matrix DrawingRoutines::m_projMatrix;
sm::Matrix DrawingRoutines::m_viewMatrix;
sm::Matrix DrawingRoutines::m_viewProjMatrix;

bool DrawingRoutines::Initialize()
{
	m_celShadingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShading");
	assert(m_celShadingShader != NULL);

	m_celShadingMutatingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShadingMutating");
	assert(m_celShadingMutatingShader != NULL);

	m_outlineShader = InterfaceProvider::GetContent()->Get<Shader>("Outline");
	assert(m_outlineShader != NULL);

	m_outlineMutatingShader = InterfaceProvider::GetContent()->Get<Shader>("OutlineMutating");
	assert(m_outlineMutatingShader != NULL);

	m_skydomeShader = InterfaceProvider::GetContent()->Get<Shader>("Skydome");
	assert(m_skydomeShader != NULL);

	m_diffTexShader = InterfaceProvider::GetContent()->Get<Shader>("DiffTex");
	assert(m_diffTexShader != NULL);

	m_diffShader = InterfaceProvider::GetContent()->Get<Shader>("Diff");
	assert(m_diffShader != NULL);

	m_grassShader = InterfaceProvider::GetContent()->Get<Shader>("Grass");
	assert(m_grassShader != NULL);

	m_celShadingShader->BindVertexChannel(0, "a_position");
	m_celShadingShader->BindVertexChannel(1, "a_normal");
	m_celShadingShader->BindVertexChannel(2, "a_coords");
	m_celShadingShader->LinkProgram();

	m_celShadingMutatingShader->BindVertexChannel(0, "a_position");
	m_celShadingMutatingShader->BindVertexChannel(1, "a_normal");
	m_celShadingMutatingShader->BindVertexChannel(2, "a_coords");
	m_celShadingMutatingShader->LinkProgram();

	m_outlineShader->BindVertexChannel(0, "a_position");
	m_outlineShader->BindVertexChannel(1, "a_normal");
	m_outlineShader->LinkProgram();

	m_outlineMutatingShader->BindVertexChannel(0, "a_position");
	m_outlineMutatingShader->BindVertexChannel(1, "a_normal");
	m_outlineMutatingShader->LinkProgram();

	m_skydomeShader->BindVertexChannel(0, "a_position");
	m_skydomeShader->BindVertexChannel(2, "a_coords");
	m_skydomeShader->LinkProgram();

	m_diffTexShader->BindVertexChannel(0, "a_position");
	m_diffTexShader->BindVertexChannel(2, "a_coords");
	m_diffTexShader->LinkProgram();

	m_diffShader->BindVertexChannel(0, "a_position");
	m_diffShader->BindVertexChannel(1, "a_coords");
	m_diffShader->BindVertexChannel(3, "a_normal");
	m_diffShader->LinkProgram();

	m_grassShader->BindVertexChannel(0, "a_position");
	m_grassShader->BindVertexChannel(2, "a_coords");
	m_grassShader->LinkProgram();

	return true;
}

void DrawingRoutines::DrawDiff(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_TRUE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);
	m_diffShader->UseProgram();
	m_diffShader->SetMatrixParameter("u_viewProjMatrix", m_projMatrix * viewMatrix);
	m_diffShader->SetParameter("u_lightPosition", m_lightPosition);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		meshParts[i]->SetupVertexPointers();

		m_diffShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		m_diffShader->SetMatrixParameter("u_worldMatrix", worldMatrix * meshParts[i]->mesh->Transform());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
}

void DrawingRoutines::DrawStreet(Model *model, Texture *diffuseTexture, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_TRUE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);
	m_diffShader->UseProgram();
	m_diffShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
	m_diffShader->SetParameter("u_lightPosition", m_lightPosition);
	m_diffShader->SetParameter("u_eyePosition", m_lightPosition);
	m_diffShader->SetTextureParameter("u_diffTex", 0, diffuseTexture->GetId());
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		meshParts[i]->SetupVertexPointers();

		m_diffShader->SetMatrixParameter("u_worldMatrix", worldMatrix * meshParts[i]->mesh->Transform());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
}

void DrawingRoutines::DrawSkydome(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &projMatrix)
{
	assert(model != NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(2);
	m_skydomeShader->UseProgram();
	m_skydomeShader->SetMatrixParameter("u_viewMatrix", viewMatrix);
	m_skydomeShader->SetMatrixParameter("u_projMatrix", projMatrix);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		m_skydomeShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glDepthMask(GL_TRUE);
}

void DrawingRoutines::DrawSprite(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(2);
	m_diffTexShader->UseProgram();
	m_diffTexShader->SetMatrixParameter("u_mvpMatrix", m_projMatrix * (viewMatrix * worldMatrix));
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_diffTexShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::DrawGrass(Model *model, Texture *colorMapTex, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	m_grassShader->UseProgram();
	m_grassShader->SetMatrixParameter("u_worldMatrix", worldMatrix);
	m_grassShader->SetMatrixParameter("u_viewProjMatrix", m_projMatrix * viewMatrix);
	m_grassShader->SetTextureParameter("u_colorMapTex", 1, colorMapTex->GetId());
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_grassShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::SetLightPosition(const sm::Vec3 &lightPosition)
{
	m_lightPosition = lightPosition;
}

void DrawingRoutines::SetEyePosition(const sm::Vec3 &eyePosition)
{
	m_eyePosition = eyePosition;
}

void DrawingRoutines::SetOutlineWidth(float outlineWidth)
{
	m_outlineWidth = outlineWidth;
}

void DrawingRoutines::SetProjectionMatrix(const sm::Matrix &projMatrix)
{
	m_projMatrix = projMatrix;

	m_viewProjMatrix = m_projMatrix * m_viewMatrix;
}

void DrawingRoutines::SetViewMatrix(const sm::Matrix &viewMatrix)
{
	m_viewMatrix = viewMatrix;

	m_viewProjMatrix = m_projMatrix * m_viewMatrix;
}

const sm::Matrix& DrawingRoutines::GetViewMatrix()
{
	return m_viewMatrix;
}

const sm::Matrix& DrawingRoutines::GetProjMatrix()
{
	return m_projMatrix;
}

const sm::Vec3& DrawingRoutines::GetEyePosition()
{
	return m_eyePosition;
}

const sm::Vec3& DrawingRoutines::GetLightPosition()
{
	return m_lightPosition;
}

bool DrawingRoutines::SetupShader(Material *material, MeshPart *meshPart, const sm::Matrix &worldatrix)
{
	if (!material->IsOpacity())
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
	}
	else
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	assert(material != NULL);

	if (material->diffuseTex != NULL &&
		material->normalTex == NULL &&
		meshPart->m_lightmap == NULL &&
		material->opacityTex == NULL)
	{
		m_diffShader->UseProgram();
		m_diffShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
		m_diffShader->SetParameter("u_lightPosition", m_lightPosition);
		m_diffShader->SetParameter("u_eyePosition", m_eyePosition);
		m_diffShader->SetMatrixParameter("u_worldMatrix", worldatrix);
		m_diffShader->SetTextureParameter("u_diffTex", 0, material->diffuseTex->GetId());
		m_diffShader->SetParameter("u_specularColor", material->specularColor);
		m_diffShader->SetParameter("u_opacity", material->Opacity());
		m_diffShader->SetParameter("u_glossiness", material->glossiness * 256.0f);
		m_diffShader->SetParameter("u_specularLevel", material->specularLevel);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		
		return true;
	}
	//else if (material->diffuseTex != NULL &&
	//	 	 material->normalTex == NULL &&
	// 	 	 meshPart->m_lightmap != NULL &&
	//		 material->opacityTex == NULL)
	//{
	//	assert(VertexInformation::HasAttrib(meshPart->m_vertexType, VertexAttrib::Coords2));

	//	m_diffLightMapShader->UseProgram();
	//	m_diffLightMapShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
	//	m_diffLightMapShader->SetParameter("u_lightPosition", m_lightPosition);
	//	m_diffLightMapShader->SetParameter("u_eyePosition", m_eyePosition);
	//	m_diffLightMapShader->SetMatrixParameter("u_worldMatrix", worldatrix);
	//	m_diffLightMapShader->SetTextureParameter("u_diffTex", 0, material->diffuseTex->GetId());
	//	m_diffLightMapShader->SetTextureParameter("u_lightmapTex", 1, meshPart->m_lightmap->GetId());
	//	m_diffLightMapShader->SetParameter("u_specularColor", material->specularColor);
	//	m_diffLightMapShader->SetParameter("u_opacity", material->Opacity());
	//	m_diffLightMapShader->SetParameter("u_glossiness", material->glossiness * 256.0f);
	//	m_diffLightMapShader->SetParameter("u_specularLevel", material->specularLevel);

	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glEnableVertexAttribArray(2);
	//	glEnableVertexAttribArray(3);
	//	glDisableVertexAttribArray(4);

	//	return true;
	//}
	//else if (material->diffuseTex != NULL &&
	//	 	 material->normalTex != NULL &&
	// 	 	 meshPart->m_lightmap == NULL &&
	//		 material->opacityTex == NULL)
	//{
	//	m_diffNormShader->UseProgram();
	//	m_diffNormShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
	//	m_diffNormShader->SetParameter("u_lightPosition", m_lightPosition);
	//	m_diffNormShader->SetParameter("u_eyePosition", m_eyePosition);
	//	//m_diffNormShader->SetMatrixParameter("u_worldMatrix", worldatrix);
	//	m_diffNormShader->SetMatrixParameter("u_worldMatrix", meshPart->mesh->Transform());
	//	m_diffNormShader->SetTextureParameter("u_diffTex", 0, material->diffuseTex->GetId());
	//	m_diffNormShader->SetTextureParameter("u_normalTex", 1, material->normalTex->GetId());
	//	m_diffNormShader->SetParameter("u_specularColor", material->specularColor);
	//	m_diffNormShader->SetParameter("u_opacity", material->Opacity());
	//	m_diffNormShader->SetParameter("u_glossiness", material->glossiness * 256.0f);
	//	m_diffNormShader->SetParameter("u_specularLevel", material->specularLevel);

	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glDisableVertexAttribArray(2);
	//	glEnableVertexAttribArray(3);
	//	glEnableVertexAttribArray(4);
	//	
	//	return true;
	//}
	//else if (material->diffuseTex == NULL &&
	//	 	 material->normalTex == NULL &&
	// 	 	 meshPart->m_lightmap == NULL &&
	//		 material->opacityTex == NULL)
	//{
	//	m_colorShader->UseProgram();
	//	m_colorShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
	//	//m_colorShader->SetMatrixParameter("u_worldMatrix", worldatrix);
	//	m_colorShader->SetMatrixParameter("u_worldMatrix", meshPart->mesh->model->m_baseTransform * meshPart->mesh->Transform());
	//	//m_sm_colorShader->SetMatrixParameter("u_worldMatrix", meshPart->mesh->Transform());
	//	m_colorShader->SetParameter("u_lightPosition", m_lightPosition);
	//	m_colorShader->SetParameter("u_eyePosition", m_eyePosition);
	//	m_colorShader->SetParameter("u_diffuseColor", material->diffuseColor);
	//	m_colorShader->SetParameter("u_specularColor", material->specularColor);
	//	m_colorShader->SetParameter("u_glossiness", material->glossiness * 256.0f);
	//	m_colorShader->SetParameter("u_specularLevel", material->specularLevel);
	//	
	//	glEnableVertexAttribArray(0);
	//	glDisableVertexAttribArray(1);
	//	glDisableVertexAttribArray(2);
	//	glEnableVertexAttribArray(3);
	//	glDisableVertexAttribArray(4);
	//	
	//	return true;
	//}
	//else if (material->diffuseTex != NULL &&
	//	 	 material->normalTex != NULL &&
	// 	 	 meshPart->m_lightmap != NULL &&
	//		 material->opacityTex == NULL)
	//{
	//	assert(VertexInformation::HasAttrib(meshPart->m_vertexType, VertexAttrib::Coords2));

	//	m_diffNormLightmapShader->UseProgram();
	//	m_diffNormLightmapShader->SetMatrixParameter("u_viewProjMatrix", m_viewProjMatrix);
	//	m_diffNormLightmapShader->SetParameter("u_lightPosition", m_lightPosition);
	//	m_diffNormLightmapShader->SetParameter("u_eyePosition", m_eyePosition);
	//	m_diffNormLightmapShader->SetMatrixParameter("u_worldMatrix", worldatrix);
	//	m_diffNormLightmapShader->SetTextureParameter("u_diffTex", 0, material->diffuseTex->GetId());
	//	m_diffNormLightmapShader->SetTextureParameter("u_normalTex", 1, material->normalTex->GetId());
	//	m_diffNormLightmapShader->SetTextureParameter("u_lightmapTex", 2, meshPart->m_lightmap->GetId());
	//	m_diffNormLightmapShader->SetParameter("u_specularColor", material->specularColor);
	//	m_diffNormLightmapShader->SetParameter("u_opacity", material->Opacity());
	//	m_diffNormLightmapShader->SetParameter("u_glossiness", material->glossiness * 256.0f);
	//	m_diffNormLightmapShader->SetParameter("u_specularLevel", material->specularLevel);
	//	
	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glEnableVertexAttribArray(2);
	//	glEnableVertexAttribArray(3);
	//	glEnableVertexAttribArray(4);
	//	
	//	return true;
	//}
	//else
	//{
	//	int d = 0;
	//}

	return false;
}

void DrawingRoutines::DrawWithMaterial(std::vector<MeshPart*> &meshParts, const sm::Matrix &worldMatrix)
{
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		if (!meshParts[i]->IsVisible())
			continue;

		if (meshParts[i]->GetMaterial() == NULL)
		{
			//assert(false);
			meshParts[i]->material = new Material();
		}

		if (SetupShader(meshParts[i]->GetMaterial(), meshParts[i], worldMatrix * meshParts[i]->mesh->Transform()))
			meshParts[i]->Draw();
	}
}
