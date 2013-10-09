#include "Taxi.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

Taxi::Taxi() :
	m_isTurningLeft(false),
	m_isTurningRight(false),
	m_isAccelerating(false)
{
	Content *content = InterfaceProvider::GetContent();

	m_taxiModel = content->Get<Model>("taxi");
	assert(m_taxiModel != NULL);

	m_position.Set(0, 0, 0);
	m_velocity.Set(0, 0, 0);
	m_turnDirection.Set(0, 0, 1);
}

Taxi::~Taxi()
{
}

void Taxi::Update(float time, float seconds)
{
	if (m_isTurningRight)
		m_turnDirection.RotateY(2.5f * seconds);

	if (m_isTurningLeft)
		m_turnDirection.RotateY(-2.5f * seconds);


	sm::Vec3 moveDirection = m_velocity.GetNormalized();
	float breakValue = 3.0f;

	if (moveDirection != sm::Vec3(0, 0, 0))
	{
		float dot = sm::Vec3::Dot(moveDirection, m_turnDirection);
		breakValue += (1.0f - dot) * 15.0f; 
	}

	if (m_isAccelerating)
		m_velocity += m_turnDirection * 20.0f * seconds;

	float speed = m_velocity.GetLength();

	if (speed > 20.0f)
		speed = 20.0f;
	if (speed > 0)
		speed -= MathUtils::Min(breakValue	 * seconds, speed);

	m_velocity.SetLength(speed);

	m_position += m_velocity * seconds;

	m_worldMatrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_turnDirection.GetReversed(), sm::Vec3(0, 1, 0));

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
