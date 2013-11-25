#include "LightsCollider.h"

LightsCollider::LightsCollider(const sm::Vec3 &position, const sm::Vec3 &direction) :
	m_position(position),
	m_direction(direction)
{
}

ColliderType LightsCollider::GetColliderType() const
{
	return ColliderType_StreetLights;
}

bool LightsCollider::CheckCollision(const Collider* collider) const
{
	return false;
}

sm::Vec3 LightsCollider::GetPosition() const
{
	return m_position;
}
