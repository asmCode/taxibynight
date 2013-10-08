#include "GameScreen.h"

#include "IGun.h"
#include "IBullet.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "Skydome.h"
#include "GameProps.h"
#include "ManCam.h"
#include "Street.h"
#include "DrawingRoutines.h"

#include "../BunniesView/IShapesRenderer.h"
#include "../BunniesView/WinShapesRenderer.h"

#include <Math/MathUtils.h>
#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>

GameScreen::GameScreen(void) :
	m_street(NULL)
{
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::Initialize()
{
	m_manCam = new ManCam();

	m_street = new Street();

	uint32_t screenWidth = Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = Environment::GetInstance()->GetScreenHeight();

	m_projMatrix = sm::Matrix::PerspectiveMatrix(MathUtils::PI / 2.0f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 1000.0f);

	return true;
}

bool GameScreen::InitResources()
{
	return false;
}

bool GameScreen::ReleaseResources()
{
	return false;
}

void GameScreen::Draw(float time, float seconds)
{
	m_street->Draw(time, seconds);
}

void GameScreen::Update(float time, float seconds)
{
	m_manCam->Process(seconds);

	sm::Matrix viewMatrix = m_manCam->GetViewMatrix();

	DrawingRoutines::SetProjectionMatrix(m_projMatrix);
	DrawingRoutines::SetLightPosition(m_manCam->GetPosition());

	m_street->SetViewMatrix(viewMatrix);
}

void GameScreen::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
}

void GameScreen::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
}

void GameScreen::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
}
