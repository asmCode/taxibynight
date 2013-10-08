#include "Skydome.h"
#include "InterfaceProvider.h"
#include "DrawingRoutines.h"

#include <Graphics/Model.h>
#include <Graphics/Content/Content.h>

#include <stddef.h>
#include <assert.h>

Skydome::Skydome()
{
	m_skydomeModel = InterfaceProvider::GetContent()->Get<Model>("skydome");
	assert(m_skydomeModel != NULL);
}

Skydome::~Skydome(void)
{
}

void Skydome::SetViewMatrix(const sm::Matrix &viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

void Skydome::SetProjMatrix(const sm::Matrix &projMatrix)
{
	m_projMatrix = projMatrix;
}

void Skydome::Update(float time, float seconds)
{
}

void Skydome::Draw(float time, float seconds)
{
	DrawingRoutines::DrawSkydome(m_skydomeModel, m_viewMatrix, m_projMatrix);
}
