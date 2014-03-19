#include "SpringCamera.h"
#include <Math/MathUtils.h>

namespace sm
{

SpringCamera::SpringCamera()
{
}

void SpringCamera::SetDestinationPosition(const Vec3& position)
{
	m_destinationPosition = position;
}

void SpringCamera::SetDestinationLookDirection(const Vec3& direction)
{
	m_destinationDirection = direction;
}

void SpringCamera::Update(float seconds)
{
	Vec3 vectorToDestination = m_destinationPosition - m_position;

	float dist = vectorToDestination.GetLength();
	if (dist < 0.001f)
		SetPosition(m_destinationPosition);
	else
	{
		Vec3 deltaTodestination = vectorToDestination * seconds * 4.0f;
		if (deltaTodestination.GetLength() > dist)
			SetPosition(m_destinationPosition);
		else
			SetPosition(m_position + deltaTodestination);
	}

	float angle = Vec3::GetAngle(m_lookDirection, m_destinationDirection);
	if (angle < 0.0001f)
		m_lookDirection = m_destinationDirection;
	else
	{
		Vec3 axis = (m_destinationDirection * m_lookDirection).GetNormalized();
		float deltaAngle = angle * seconds * 2.0f;
		Matrix rotMatrix = Matrix::RotateAxisMatrix(MathUtils::Min(angle, deltaAngle), axis);
		m_lookDirection = rotMatrix * m_lookDirection;
	}
}

} /* namespace sm */
