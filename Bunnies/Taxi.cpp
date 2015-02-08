#include "Taxi.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "PedsManager.h"
#include "Street.h"
#include "BoxCollider.h"
#include "CarController.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/BoundingBox.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Audio/SoundManager.h>
#include <Math/MathUtils.h>
#include <Utils/Randomizer.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

Taxi *Taxi::m_instance;

Taxi::Taxi() :
	m_isOccupied(false)
{
	m_instance = this;

	Content *content = InterfaceProvider::GetContent();

	m_taxiModel = content->Get<Model>("taxi");
	assert(m_taxiModel != NULL);

	m_lights = content->Get<Model>("lights");
	assert(m_lights != NULL);

	m_bladeModel = content->Get<Model>("blade");
	assert(m_bladeModel != NULL);

	m_normalTex = content->Get<Texture>("cabby_diff");
	assert(m_normalTex != NULL);

	m_carmaTex = content->Get<Texture>("cabby_carma_diff");
	assert(m_carmaTex != NULL);

	m_taxiMat = content->Get<Material>("taxi");
	assert(m_taxiMat != NULL);

	m_shadow = content->Get<Model>("taxi_shadow");
	assert(m_shadow != NULL);

	m_antiMagnet = content->Get<Model>("antimagnet");
	assert(m_antiMagnet != NULL);

	m_carController = new CarController();
	m_carController->Initialize();
	m_carController->SetParameters(
		8.0f * 1000.0f,
		-1.8f,
		1.8f,
		1000.0f,
		15.0f);

	m_worldMatrix = m_carController->GetTransform();

	m_frontRightWheel = m_taxiModel->FindMesh("wheel_front_right");
	m_frontLeftWheel = m_taxiModel->FindMesh("wheel_front_left");

	m_baseFrontLeftWheelPosition = m_frontLeftWheel->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseFrontRightWheelPosition = m_frontRightWheel->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseBackLeftWheelPosition = m_taxiModel->FindMesh("wheel_back_left")->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseBackRightWheelPosition = m_taxiModel->FindMesh("wheel_back_right")->m_worldMatrix * sm::Vec3(0, 0, 0);

	m_backFrontWheelsDistance = (m_baseFrontRightWheelPosition - m_baseBackRightWheelPosition).GetLength();

	m_boundsTopLeft = m_taxiModel->FindMesh("helper.bounds.top-left")->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_boundsBottomRight = m_taxiModel->FindMesh("helper.bounds.bottom-right")->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_boundsTopLeft.y = 0;
	m_boundsBottomRight.y = 0;
	m_boundsTopRight.Set(m_boundsBottomRight.x, 0, m_boundsTopLeft.z);
	m_boundsBottomLeft.Set(m_boundsTopLeft.x, 0, m_boundsBottomRight.z);

	m_boxCollider = new BoxCollider(
		(m_boundsTopLeft + m_boundsBottomRight) * 0.5f,
		sm::Vec3(
			m_boundsTopRight.x - m_boundsTopLeft.x,
			0, 
			m_boundsBottomRight.z - m_boundsTopRight.z));
			

}

void Taxi::Reset()
{
	m_antiMagnetRor1.Set(0, 0, 0, 0);
	m_antiMagnetRor2.Set(0, 0, 0, 0);

	m_isOccupied = false;

	m_revard = 0.0f;
	m_timeLeft = 0.0f;
}

Taxi* Taxi::GetInstance()
{
	return m_instance;
}

Taxi::~Taxi()
{
}

void Taxi::Update(float time, float seconds)
{
	if (PedsManager::Instance->IsAntiMagnetMode())
	{
		m_antiMagnetRor1.x += seconds * 0.7f;
		m_antiMagnetRor1.y += seconds * 1.5f;
		m_antiMagnetRor1.z += seconds * 2.3f;
		m_antiMagnetRor1.w += seconds * 0.4f;

		m_antiMagnetRor2.x += seconds * 2.25f;
		m_antiMagnetRor2.y += seconds * 0.83f;
		m_antiMagnetRor2.z += seconds * 1.1f;
		m_antiMagnetRor2.w += seconds * 0.8f;
	}

	if (IsOccupied())
	{
		PedsManager::Instance->IsTakeYourTimeMode() ? m_timeLeft -= seconds * 0.5f : m_timeLeft -= seconds;
		if (m_timeLeft < 0.0f)
			m_timeLeft = 0.0f;
	}

	m_carController->Update(seconds);
	m_worldMatrix = m_carController->GetTransform();

	SoundManager::GetInstance()->SetEnginePitch((MathUtils::Abs(m_carController->GetSpeed()) / 30.0f) * 1.0f + 1.0f);

	/*
	m_frontRightWheel->Transform() =
		m_frontRightWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontRightWheel->m_worldInverseMatrix;

	m_frontLeftWheel->Transform() =
		m_frontLeftWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontLeftWheel->m_worldInverseMatrix;
	*/
}

void Taxi::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(m_taxiModel->m_meshParts, m_worldMatrix);

	if (PedsManager::Instance->IsCarmageddonMode())
	{
		DrawingRoutines::DrawWithMaterial(m_bladeModel->m_meshParts, m_worldMatrix);
		m_taxiMat->diffuseTex = m_carmaTex;
	}
	else
	{
		m_taxiMat->diffuseTex = m_normalTex;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawingRoutines::DrawUnlit(m_shadow->m_meshParts[0], sm::Matrix::TranslateMatrix(-0.4f, 0, 0.4f) * m_worldMatrix);
	glDisable(GL_BLEND);
}

void Taxi::SetTurn(float turnValue)
{
	if (turnValue == 0.0f)
		m_carController->Steer(CarController::Steer_None);
	if (turnValue == -1.0f)
		m_carController->Steer(CarController::Steer_Right);
	if (turnValue == 1.0f)
		m_carController->Steer(CarController::Steer_Left);
}

void Taxi::SetAcceleration(float acc)
{
	//if (PedsManager::Instance->IsFeelThePowerMode() && acc > 0.0f)
		//acc *= 3.0f;

	// TODO: uwzglednij peel the power ustawiajac wieksza moc w carphysics
	
	m_carController->Accelerate(acc == 1.0f);
	m_carController->Break(acc == -1.0f);
}

sm::Vec3 Taxi::GetPosition() const
{
	return m_carController->GetPosition();
}

sm::Vec3 Taxi::GetDirection() const
{
	return m_carController->GetDirection();
}

float Taxi::GetSpeed() const
{
	return m_carController->GetSpeed();
}

bool Taxi::IsOccupied() const
{
	return m_isOccupied;
}

void Taxi::SetOccupied(const sm::Vec3 &passengerTarget,
					   float revard,
					   float timeLeft)
{
	m_isOccupied = true;
	m_revard = revard;
	m_timeLeft = timeLeft;
	m_passengerTarget = passengerTarget;
}

void Taxi::SetFree()
{
	m_isOccupied = false;
}

sm::Vec3 Taxi::GetPassengerTarget() const
{
	return m_passengerTarget;
}

void Taxi::DrawTransparencies()
{
	//DrawingRoutines::DrawWithMaterial(m_lights->m_meshParts, m_worldMatrix, true);

	sm::Vec3 position = m_carController->GetPosition();

	if (PedsManager::Instance->IsAntiMagnetMode())
	{
		sm::Matrix rot1 =
			sm::Matrix::RotateAxisMatrix(
			m_antiMagnetRor1.w,
			sm::Vec3(sinf(m_antiMagnetRor1.x), sinf(m_antiMagnetRor1.y), sinf(m_antiMagnetRor1.z)).GetNormalized());

		sm::Matrix rot2 =
			sm::Matrix::RotateAxisMatrix(
			m_antiMagnetRor2.w,
			sm::Vec3(sinf(m_antiMagnetRor2.x), sinf(m_antiMagnetRor2.y), sinf(m_antiMagnetRor2.z)).GetNormalized());
		
		DrawingRoutines::DrawAntimagnet(
			m_antiMagnet->m_meshParts[0],
			m_worldMatrix * sm::Matrix::ScaleMatrix(7.0f, 3.5f, 7.0f) * rot1,
			NULL,
			position + sm::Vec3(-70.0f, 15.0f, -70.0f));

		DrawingRoutines::DrawAntimagnet(
			m_antiMagnet->m_meshParts[0],
			m_worldMatrix * sm::Matrix::ScaleMatrix(7.0f, 3.5f, 7.0f) * rot2,
			NULL,
			position + sm::Vec3(-70.0f, 15.0f, -70.0f));
	}
}
