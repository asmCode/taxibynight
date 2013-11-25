#include "Collider.h"

void Collider::SetTransform(const sm::Matrix& transform)
{
	m_transform = transform;
	m_transformInverted = m_transform.GetInversed();
}

