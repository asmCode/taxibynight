#include "Car.h"
#include "Street.h"
#include "StreetSegment.h"
#include "StreetPiece.h"
#include "StreetLights.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include <Math/MathUtils.h>

Car::Car(BoxCollider* boxCollider) :
	m_isActive(false),
	m_worldMatrix(sm::Matrix::Identity),
	m_speed(0.0f),
	m_acceleration(0.0f),
	m_maxSpeed(30.0f),
	m_boxCollider(boxCollider)
{
}

Car::~Car()
{
}

void Car::Update(float time, float seconds)
{
	float distance = (m_destination - m_position).GetLength();

	if (distance < 1.0f)
		GetNewDestination(true);

	DriveToDestination(seconds);
}

void Car::SetActive(const sm::Vec3 &initialPosition)
{
	m_isActive = true;

	m_position = initialPosition;
	m_destination = m_position;

	StreetSegment *ss = Street::Instance->GetSegmentAtPosition(m_position);
	assert(ss != NULL);
	assert(ss->GetStreetPiece()->HasRoad());

	m_streetPath = ss->GetRandomPathAtPosition(m_position);
}

void Car::SetInactive()
{
	m_isActive = false;
}

bool Car::IsActive() const
{
	return m_isActive;
}

bool Car::CanDrive()
{
	return m_streetPath.CanDrive();
}

void Car::DriveToDestination(float seconds)
{
	if (CanDrive())
	{
		StreetLights *siblingStreetLights = m_streetPath.GetContinousSegment()->GetLights(m_position);

		if (siblingStreetLights != NULL && !siblingStreetLights->CanDrive())
		{
			if (m_speed > 5.0f)
				m_acceleration = -30.0f;
			else
				m_acceleration = 30.0f;
		}
		else
		{
			if (m_speed != m_maxSpeed)
				m_acceleration = 10.0f;
			else
				m_acceleration = 0.0f;
		}
	}
	else
	{
		if (m_speed > 0.0f)
			m_acceleration = -50.0f;
		else
			m_acceleration = 0.0f;
	}

	m_speed = MathUtils::Clamp(m_speed + m_acceleration * seconds, 0.0f, m_maxSpeed);

	sm::Vec3 direction = m_destination - m_position;
	float distance = direction.GetLength();
	direction.Normalize();

	sm::Vec3 moveVector;

	if (distance < 0.01f) // BETON!!!
	{
		//direction = sm::Vec3(0, 0, 1);
		moveVector.Set(0, 0, 0);

		m_position = m_destination;
	}
	else
	{
		moveVector = direction * m_speed;
	}

	m_position += moveVector * seconds;

	m_worldMatrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(direction, sm::Vec3(0, 1, 0));

	m_boxCollider->SetTransform(m_worldMatrix);

	if (CollisionManager::GetInstance()->CheckCollision(this))
	{
		int chuj = 0;
		chuj++;
	}
}

void Car::GetNewDestination(bool atTheEdge)
{
	if (m_streetPath.IsAtTheEnd())
	{
		StreetSegment *ss = m_streetPath.GetContinousSegment();
		assert(ss != NULL);

		if (ss == NULL)
			return;

		m_streetPath = ss->GetRandomPathAtPosition(m_position);
	}

	m_destination = m_streetPath.GetNextPosition();
}

const sm::Vec3& Car::GetPosition() const
{
	return m_position;
}

const sm::Matrix& Car::GetWorldMatrix() const
{
	return m_worldMatrix;
}

const Collider* Car::GetCollider() const
{
	return m_boxCollider;
}