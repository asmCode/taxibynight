#include "DiffLightEffect.h"
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

DiffLightEffect::DiffLightEffect(Shader* shader)
{
	m_shader = shader;
	m_worldMatrixLocation = m_shader->GetUniformLocation("u_worldMatrix");
	m_viewProjMatrixLocation = m_shader->GetUniformLocation("u_viewProjMatrix");
	m_lightPositionLocation = m_shader->GetUniformLocation("u_lightPosition");
	m_textureLocation = m_shader->GetUniformLocation("u_diffTex");
}
	
void DiffLightEffect::Begin()
{
	m_shader->UseProgram();
	
	/*
	m_shader->SetMatrixParameter(m_worldMatrixLocation, m_worldMatrix);
	m_shader->SetMatrixParameter(m_viewProjMatrixLocation, m_viewProjMatrix);
	m_shader->SetParameter(m_lightPositionLocation, m_lightPosition);
	m_shader->SetTextureParameter(m_textureLocation, m_texture->GetId(), 0);
	*/
}
	
void DiffLightEffect::SetWorldMatrix(const sm::Matrix& worldMatrix)
{
	m_shader->SetMatrixParameter(m_worldMatrixLocation, worldMatrix);
}

void DiffLightEffect::SetViewProjMatrix(const sm::Matrix& viewProjMatrix)
{
	m_shader->SetMatrixParameter(m_viewProjMatrixLocation, viewProjMatrix);
}

void DiffLightEffect::SetLightPosition(const sm::Vec3& lightPosition)
{
	m_shader->SetParameter(m_lightPositionLocation, lightPosition);
}

void DiffLightEffect::SetTexture(Texture* texture)
{
	m_shader->SetTextureParameter(m_textureLocation, 0, texture->GetId());
}

