#include "GameScreen.h"

#include "PedsManager.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "GameProps.h"
//#include "ManCam.h"
#include "Street.h"
#include "DrawingRoutines.h"
#include "Taxi.h"
#include "Arrow.h"
#include "Billboard.h"
#include "PlaceIndicator.h"
#include "HUD.h"

#include <Math/MathUtils.h>
#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Texture.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/Content/Content.h>
#include <Utils/Log.h>

#include <FGraphicsOpengl2.h>
using namespace Tizen::Graphics::Opengl;

GameScreen *GameScreen::m_instance;

GameScreen::GameScreen(void) :
	m_street(NULL),
	m_taxi(NULL),
	m_pedsManager(NULL)
{
	m_instance = this;

	m_isTurnRightPressed = false;
	m_isTurnLeftPressed = false;
}

GameScreen::~GameScreen(void)
{
}

GameScreen *GameScreen::GetInstance()
{
	return m_instance;
}

bool GameScreen::Initialize()
{
	Billboard::Initialize();

	//m_manCam = new ManCam();

	m_taxi = new Taxi();
	m_pedsManager = new PedsManager(m_taxi->GetPosition());
	m_street = new Street(m_pedsManager);
	m_street->SetInitialVisibility(m_taxi->GetPosition());

	m_arrow = new Arrow();
	m_placeIndicator = new PlaceIndicator();

	m_hud = HUD::Create(this);

	uint32_t screenWidth = TaxiGame::Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = TaxiGame::Environment::GetInstance()->GetScreenHeight();

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
	glEnable(GL_DEPTH_TEST);

	m_street->Draw(time, seconds);
	m_taxi->Draw(time, seconds);
	m_pedsManager->Draw(time, seconds);
	m_arrow->Draw(time, seconds);
	m_placeIndicator->Draw(time, seconds);

	InterfaceProvider::GetSpriteBatch()->Begin();
	m_hud->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void GameScreen::Update(float time, float seconds)
{
	SimulatePress();

	m_taxi->Update(time, seconds);

	m_street->SetTaxiPosition(m_taxi->GetPosition());
	m_street->Update(time, seconds);

	m_pedsManager->SetTaxiPosition(m_taxi->GetPosition());
	m_pedsManager->Update(time, seconds);

	if (m_taxi->IsOccupied())
	{
		m_arrow->SetDirection((m_taxi->GetPassengerTarget() - m_taxi->GetPosition()).GetNormalized());
		m_arrow->Update(time, seconds);
	}

	//m_manCam->Process(seconds);

	sm::Vec3 taxiPosition = m_taxi->GetPosition();
	sm::Vec3 camPosition = taxiPosition + sm::Vec3(0, 10, -4);
	sm::Vec3 camLook = (camPosition - (taxiPosition + sm::Vec3(0, 0, +2))).GetNormalized();
	m_viewMatrix =
		sm::Matrix::TranslateMatrix(camPosition) *
		sm::Matrix::CreateLookAt2(camLook, sm::Vec3(0, 1, 0));

	m_viewMatrix = m_viewMatrix.GetInversed();

	//m_viewMatrix = m_manCam->GetViewMatrix();
	camPosition = m_viewMatrix.GetInversed() * sm::Vec3(0, 0, 0);

	m_placeIndicator->Update(time, seconds, m_projMatrix * m_viewMatrix);

	m_hud->Update(time, seconds);

	DrawingRoutines::SetProjectionMatrix(m_projMatrix);
	DrawingRoutines::SetViewMatrix(m_viewMatrix);
	DrawingRoutines::SetLightPosition(camPosition);
	DrawingRoutines::SetEyePosition(camPosition);
}

void GameScreen::SetOccupiedMode()
{
	m_arrow->SetDirection(m_taxi->GetPassengerTarget());
	m_arrow->SetActive(true);
	m_placeIndicator->SetActive(true);
	m_placeIndicator->SetPosition(m_taxi->GetPassengerTarget());
}

void GameScreen::SetFreeMode()
{
	m_arrow->SetActive(false);
	m_placeIndicator->SetActive(false);
}

void GameScreen::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
	m_hud->HandlePress(pointIndex, point);
}

void GameScreen::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	m_hud->HandleRelease(pointIndex, point);
}

void GameScreen::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
}

void GameScreen::TurnLeftButtonPressed(bool isPressed)
{
	m_isTurnLeftPressed = isPressed;

	if (!m_isTurnRightPressed && !m_isTurnLeftPressed)
		m_taxi->SetTurn(0.0f);
	else if (m_isTurnRightPressed)
		m_taxi->SetTurn(-1.0f);
	else if (m_isTurnLeftPressed)
		m_taxi->SetTurn(1.0f);
}

void GameScreen::TurnRightButtonPressed(bool isPressed)
{
	m_isTurnRightPressed = isPressed;

	if (!m_isTurnRightPressed && !m_isTurnLeftPressed)
		m_taxi->SetTurn(0.0f);
	else if (m_isTurnRightPressed)
		m_taxi->SetTurn(-1.0f);
	else if (m_isTurnLeftPressed)
		m_taxi->SetTurn(1.0f);
}

void GameScreen::AccelerationButtonPressed(bool isPressed)
{
	if (isPressed)
		m_taxi->Accelerate(true);
	else
		m_taxi->Accelerate(false);
}

void GameScreen::SimulatePress()
{
	return;

//	if (GetAsyncKeyState(VK_UP) & 0x8000)
//		AccelerationButtonPressed(true);
//	else
//		AccelerationButtonPressed(false);
//
//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//		TurnLeftButtonPressed(true);
//	else
//		TurnLeftButtonPressed(false);
//
//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//		TurnRightButtonPressed(true);
//	else
//		TurnRightButtonPressed(false);
}
