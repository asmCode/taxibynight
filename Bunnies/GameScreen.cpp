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
#include "Taxi.h"

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
	m_street(NULL),
	m_taxi(NULL)
{
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::Initialize()
{
	m_manCam = new ManCam();

	m_street = new Street();
	m_taxi = new Taxi();

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

	m_taxi->Draw(time, seconds);
}

void GameScreen::Update(float time, float seconds)
{
	SimulatePress();

	m_taxi->Update(time, seconds);

	m_street->Update(time, seconds);

	m_manCam->Process(seconds);

	sm::Vec3 taxiPosition = m_taxi->GetPosition();
	sm::Vec3 camPosition = taxiPosition + sm::Vec3(0, 10, -6);
	sm::Vec3 camLook = (camPosition - (taxiPosition + sm::Vec3(0, 0, +4))).GetNormalized();
	m_viewMatrix =
		sm::Matrix::TranslateMatrix(camPosition) *
		sm::Matrix::CreateLookAt2(camLook, sm::Vec3(0, 1, 0));

	m_viewMatrix = m_viewMatrix.GetInversed();

	//m_viewMatrix = m_manCam->GetViewMatrix();

	DrawingRoutines::SetProjectionMatrix(m_projMatrix);
	DrawingRoutines::SetViewMatrix(m_viewMatrix);
	DrawingRoutines::SetLightPosition(camPosition);
	DrawingRoutines::SetEyePosition(camPosition);
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

void GameScreen::TurnLeftButtonPressed()
{
	m_taxi->TurnLeft();
}

void GameScreen::TurnRightButtonPressed()
{
	m_taxi->TurnRight();
}

void GameScreen::AccelerationButtonPressed()
{
	m_taxi->Accelerate();
}

void GameScreen::SimulatePress()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		AccelerationButtonPressed();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		TurnLeftButtonPressed();

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		TurnRightButtonPressed();
}

