#include "Collider.h"

Collider::Collider() :
	m_colliderId(ColliderId_Default)
{

}

void Collider::SetTransform(const sm::Matrix& transform)
{
	m_transform = transform;
	m_transformInverted = m_transform.GetInversed();
}

void Collider::SetColliderId(ColliderId colliderId)
{
	m_colliderId = colliderId;
}

ColliderId Collider::GetColliderId() const
{
	return m_colliderId;
}
