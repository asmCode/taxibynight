#include "Taxi.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "Street.h"
#include "BoxCollider.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/BoundingBox.h>
#include <Graphics/Texture.h>
#include <Audio/SoundManager.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

Taxi *Taxi::m_instance;

Taxi::Taxi() :
	m_turnValue(0.0f),
	m_isAccelerating(false),
	m_speed(0.0f),
	m_wheelsAngle(0.0f),
	m_isOccupied(false)
{
	m_instance = this;

	Content *content = InterfaceProvider::GetContent();

	m_taxiModel = content->Get<Model>("taxi");
	assert(m_taxiModel != NULL);

	m_position.Set(100, 0, 100);
	m_velocity.Set(0, 0, 0);
	m_turnDirection.Set(0, 0, -1);
	m_carDirection.Set(0, 0, -1);
	m_wheelsAngle = 0.0f;

	m_worldMatrix = sm::Matrix::TranslateMatrix(m_position);

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
}

void Taxi::Reset()
{
	m_speed = 0.0f;

	m_position.Set(100, 0, 100);
	m_worldMatrix = sm::Matrix::TranslateMatrix(m_position);
	m_velocity.Set(0, 0, 0);
	m_turnDirection.Set(0, 0, -1);
	m_carDirection.Set(0, 0, -1);

	m_isOccupied = false;

	m_wheelsAngle = 0.0f;
	m_isAccelerating = false;
	m_turnValue = 0.0f;
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
	sm::Vec3 oldPos = m_position;

	if (IsOccupied())
	{
		m_timeLeft -= seconds;
		if (m_timeLeft < 0.0f)
			m_timeLeft = 0.0f;
	}

	sm::Vec3 turnPivot;
	sm::Matrix turnMatrix;
	float pivotDistance = 0.0f;

	if (m_isAccelerating)
	{
		m_speed += 10.0f * seconds;
	}

	m_speed -= 5.0f * seconds;
	m_speed = MathUtils::Clamp(m_speed, 0.0f, 12.0f);

	SoundManager::GetInstance()->SetEnginePitch((m_speed / 12.0f) * 4.0f + 1.0f);

	m_wheelsAngle += 2.0f * m_turnValue * seconds;

	m_wheelsAngle = MathUtils::Clamp(m_wheelsAngle, -MathUtils::PI4, MathUtils::PI4);

	if (m_wheelsAngle != 0.0f)
	{
		if (m_wheelsAngle < 0.0)
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(fabs(m_wheelsAngle));
			turnPivot = sm::Vec3(m_baseBackRightWheelPosition.x + pivotDistance, 0, m_baseBackRightWheelPosition.z);
		}
		else
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(fabs(m_wheelsAngle));
			turnPivot = sm::Vec3(m_baseBackLeftWheelPosition.x - pivotDistance, 0, m_baseBackLeftWheelPosition.z);
		}

		float angleSpeed = m_speed / (2.0f * MathUtils::PI * MathUtils::Abs(turnPivot.x));

		sm::Matrix turnMatrixNormal =
			sm::Matrix::RotateAxisMatrix(
				angleSpeed * (MathUtils::PI * 2.0f) * seconds * MathUtils::Sign(m_wheelsAngle),
				0, 1, 0);

		turnPivot = m_worldMatrix * turnPivot;
		turnPivot.y = 0.0f;

		turnMatrix =
			sm::Matrix::TranslateMatrix(turnPivot) *
			turnMatrixNormal *
			sm::Matrix::TranslateMatrix(turnPivot.GetReversed());

		sm::Vec3 prevCarDirection = m_carDirection;
		m_carDirection = turnMatrixNormal * m_carDirection;
		m_carDirection.Normalize();

	
		float angleDiff = sm::Vec3::GetAngle(prevCarDirection, m_carDirection);
		m_wheelsAngle -= angleDiff * MathUtils::Sign(m_wheelsAngle);

		m_position = turnMatrix * m_position;
	}
	else
		m_position += m_carDirection * m_speed * seconds;

	sm::Matrix newWorldMatrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));

	sm::Vec3 boundsTopLeftWorldOld = m_worldMatrix * m_boundsTopLeft;
	sm::Vec3 boundsBottomLeftWorldOld = m_worldMatrix * m_boundsBottomLeft;
	sm::Vec3 boundsTopLeftWorldNew = newWorldMatrix * m_boundsTopLeft;

	sm::Vec3 collisionNormal;
	sm::Vec3 collisionPoint;
	if (Street::Instance->GetCollistion(boundsTopLeftWorldOld, boundsTopLeftWorldNew, collisionPoint, collisionNormal))
	{
		collisionPoint += collisionNormal * 0.01f;

		sm::Vec3 toCollisionTarget = collisionPoint - boundsTopLeftWorldOld;
		sm::Vec3 fromCollisionTarget = sm::Vec3::Reflect(collisionNormal, toCollisionTarget);
		sm::Vec3 correntPosition = boundsTopLeftWorldOld + toCollisionTarget + fromCollisionTarget;
		sm::Vec3 deltaMove = collisionPoint - boundsTopLeftWorldOld;

		m_carDirection = (collisionPoint - boundsBottomLeftWorldOld).GetNormalized();

		m_position = oldPos + deltaMove;

		m_worldMatrix =
			sm::Matrix::TranslateMatrix(m_position) *
			sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));
	}
	else
		m_worldMatrix = newWorldMatrix;

	m_frontRightWheel->Transform() =
		m_frontRightWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontRightWheel->m_worldInverseMatrix;

	m_frontLeftWheel->Transform() =
		m_frontLeftWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontLeftWheel->m_worldInverseMatrix;
}

void Taxi::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(m_taxiModel->m_meshParts, m_worldMatrix);
}

void Taxi::SetTurn(float turnValue)
{
	m_turnValue = turnValue;
}

void Taxi::Accelerate(bool accelerate)
{
	m_isAccelerating = accelerate;
}

const sm::Vec3& Taxi::GetPosition() const
{
	return m_position;
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
