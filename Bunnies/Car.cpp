#include "Car.h"
#include "Street.h"
#include "StreetSegment.h"
#include "StreetPiece.h"
#include <Math/MathUtils.h>

Car::Car() :
	m_isActive(false),
	m_worldMatrix(sm::Matrix::Identity),
	m_speed(0.0f),
	m_acceleration(0.0f),
	m_maxSpeed(30.0f)
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
	return true;
}

void Car::DriveToDestination(float seconds)
{
	if (CanDrive())
	{
		if (m_speed != m_maxSpeed)
			m_acceleration = 10.0f;
	}
	else
	{
		if (m_speed > 0.0f)
			m_acceleration = -20.0f;
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
