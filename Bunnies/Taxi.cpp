#include "Taxi.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

Taxi *Taxi::m_instance;

Taxi::Taxi() :
	m_isTurningLeft(false),
	m_isTurningRight(false),
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

	m_frontRightWheel = m_taxiModel->FindMesh("wheel_front_right");
	m_frontLeftWheel = m_taxiModel->FindMesh("wheel_front_left");

	m_baseFrontLeftWheelPosition = m_frontLeftWheel->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseFrontRightWheelPosition = m_frontRightWheel->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseBackLeftWheelPosition = m_taxiModel->FindMesh("wheel_back_left")->m_worldMatrix * sm::Vec3(0, 0, 0);
	m_baseBackRightWheelPosition = m_taxiModel->FindMesh("wheel_back_right")->m_worldMatrix * sm::Vec3(0, 0, 0);

	m_backFrontWheelsDistance = (m_baseFrontRightWheelPosition - m_baseBackRightWheelPosition).GetLength();

	m_worldMatrix = sm::Matrix::IdentityMatrix();
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
	sm::Vec3 turnPivot;
	sm::Matrix turnMatrix;
	float pivotDistance = 0.0f;

	if (m_isAccelerating)
	{
		m_speed += 10.0f * seconds;
	}

	m_speed -= 5.0f * seconds;
	m_speed = MathUtils::Clamp(m_speed, 0.0f, 12.0f);

	bool notTurning = true;
	if (m_isTurningRight)
	{
		m_wheelsAngle -= 2.0 * seconds;
		notTurning = false;
	}

	if (m_isTurningLeft)
	{
		m_wheelsAngle += 2.0f * seconds;
		notTurning = false;
	}

	/*if (notTurning)
	{
		if (m_wheelsAngle > 0.0)
			m_wheelsAngle -= MathUtils::Min(m_wheelsAngle, 2.0f * seconds);
	
		if (m_wheelsAngle < 0.0)
			m_wheelsAngle += MathUtils::Min(MathUtils::Abs(m_wheelsAngle), 2.0f * seconds);
	}*/

	m_wheelsAngle = MathUtils::Clamp(m_wheelsAngle, -MathUtils::PI4, MathUtils::PI4);

	if (m_wheelsAngle != 0.0f)
	{
		if (m_wheelsAngle < 0.0)
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(abs(m_wheelsAngle));
			turnPivot = sm::Vec3(m_baseBackRightWheelPosition.x + pivotDistance, 0, m_baseBackRightWheelPosition.z);
		}
		else
		{
			pivotDistance = m_backFrontWheelsDistance / tanf(abs(m_wheelsAngle));
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

		//if (notTurning)
		{
			float angleDiff = sm::Vec3::GetAngle(prevCarDirection, m_carDirection);
			m_wheelsAngle -= angleDiff * MathUtils::Sign(m_wheelsAngle);
		}

		m_position = turnMatrix * m_position;
	}
	else
		m_position += m_carDirection * m_speed * seconds;

	m_worldMatrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_carDirection.GetReversed(), sm::Vec3(0, 1, 0));

	m_frontRightWheel->Transform() =
		m_frontRightWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontRightWheel->m_worldInverseMatrix;

	m_frontLeftWheel->Transform() =
		m_frontLeftWheel->m_worldMatrix *
		sm::Matrix::RotateAxisMatrix(m_wheelsAngle, 0, 1, 0) *
		m_frontLeftWheel->m_worldInverseMatrix;

	m_isTurningLeft = false;
	m_isTurningRight = false;
	m_isAccelerating = false;
}

void Taxi::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(m_taxiModel->m_meshParts, m_worldMatrix);
}

void Taxi::TurnLeft()
{
	m_isTurningLeft = true;
}

void Taxi::TurnRight()
{
	m_isTurningRight = true;
}

void Taxi::Accelerate()
{
	m_isAccelerating = true;
}

const sm::Vec3& Taxi::GetPosition() const
{
	return m_position;
}

bool Taxi::IsOccupied() const
{
	return m_isOccupied;
}

void Taxi::SetOccupied(const sm::Vec3 &passengerTarget)
{
	m_isOccupied = true;
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