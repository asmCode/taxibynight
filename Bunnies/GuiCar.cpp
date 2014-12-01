#include "GuiCar.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Audio/SoundManager.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include <Utils/Randomizer.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

GuiCar::GuiCar() :
	m_carModel(NULL),
	m_shadow(NULL)
{
	Content *content = InterfaceProvider::GetContent();

	m_carModel = content->Get<Model>("car3");
	assert(m_carModel != NULL);

	m_shadow = content->Get<Model>("taxi_shadow");
	assert(m_shadow != NULL);

	m_worldMatrix = sm::Matrix::TranslateMatrix(-1, -0.5f, 0);

	m_camera.SetPosition(sm::Vec3(-4, 2, -4));
	m_camera.SetLookDirection(m_camera.GetPosition().GetNormalized().GetReversed());
}

// PRZEROB TO GOWNO TAK, ZEBY MOZNA BYLO W TEJ KLASIE ZMIENIAC DOWOLNIE SAMOCHODY I ICH DECALE

GuiCar::~GuiCar()
{
}

void GuiCar::Update(float time, float seconds)
{
}

void GuiCar::Draw(float time, float seconds)
{
	DrawingRoutines::SetLightPosition(m_camera.GetPosition() + sm::Vec3(0, 2, 0));
	DrawingRoutines::SetEyePosition(m_camera.GetPosition());
	DrawingRoutines::SetViewMatrix(m_camera.GetViewMatrix());

	DrawingRoutines::DrawWithMaterial(m_carModel->m_meshParts, m_worldMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawingRoutines::DrawUnlit(m_shadow->m_meshParts[0], sm::Matrix::TranslateMatrix(-0.4f, 0, 0.4f) * m_worldMatrix);
	glDisable(GL_BLEND);
}
