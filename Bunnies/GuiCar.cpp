#include "GuiCar.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "MeshUtils.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Audio/SoundManager.h>
#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include <Utils/Randomizer.h>
#include <Graphics/ModelLoader.h>
#include <Graphics/TextureLoader.h>
#include <Graphics/MaterialLoader.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

GuiCar::GuiCar(const std::string& carsPath) :
	m_carModel(NULL),
	m_decalTexture(NULL),
	m_shadow(NULL),
	m_carsPath(carsPath),
	m_show(false)
{
	Content *content = InterfaceProvider::GetContent();

	m_shadow = content->Get<Model>("taxi_shadow");
	assert(m_shadow != NULL);

	m_commonCarMaterial = MaterialLoader::LoadFromFile(carsPath + "common.mat");
	assert(m_commonCarMaterial != NULL);

	m_worldMatrix = sm::Matrix::TranslateMatrix(-1, -0.5f, 0);

	m_camera.SetPosition(sm::Vec3(-4, 2, -4));
	m_camera.SetLookDirection(m_camera.GetPosition().GetNormalized().GetReversed());
}

GuiCar::~GuiCar()
{
}

void GuiCar::Update(float time, float seconds)
{
}

void GuiCar::Draw(float time, float seconds)
{
	if (!m_show)
		return;

	assert(m_carModel != NULL);
	assert(m_decalTexture != NULL);

	DrawingRoutines::SetLightPosition(m_camera.GetPosition() + sm::Vec3(0, 2, 0));
	DrawingRoutines::SetEyePosition(m_camera.GetPosition());
	DrawingRoutines::SetViewMatrix(m_camera.GetViewMatrix());

	DrawingRoutines::DrawWithMaterial(m_carModel->m_meshParts, m_worldMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawingRoutines::DrawUnlit(m_shadow->m_meshParts[0], sm::Matrix::TranslateMatrix(-0.4f, 0, 0.4f) * m_worldMatrix);
	glDisable(GL_BLEND);
}

void GuiCar::UnloadAll()
{
	UnloadCar();
	UnloadDecal();
}

void GuiCar::LoadCar(const std::string& carId)
{
	if (m_currentCarId == carId)
		return;

	UnloadCar();
	UnloadDecal();

	m_carModel = ModelLoader::LoadFromFile(m_carsPath + carId + ".geo");
	assert(m_carModel);

	m_currentCarId = carId;
}
void GuiCar::LoadDecal(const std::string& decalId)
{
	assert(m_carModel != NULL);

	if (m_currentDecalId == decalId)
		return;

	UnloadDecal();

	m_decalTexture = TextureLoader::Load(m_carsPath + decalId + ".png");
	assert(m_decalTexture);

	m_currentDecalId = decalId;

	m_commonCarMaterial->diffuseTex = m_decalTexture;
	MeshUtils::SetMaterial(m_carModel, m_commonCarMaterial);
}

void GuiCar::Show(bool show)
{
	m_show = show;
}

void GuiCar::UnloadCar()
{
	if (m_carModel != NULL)
	{
		delete m_carModel;
		m_carModel = NULL;
		m_currentCarId = "";
	}
}

void GuiCar::UnloadDecal()
{
	if (m_decalTexture != NULL)
	{
		delete m_decalTexture;
		m_decalTexture = NULL;
		m_currentDecalId = "";
	}
}
