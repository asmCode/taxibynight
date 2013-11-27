#include "LightsCollider.h"
#include "CollisionInfo.h"
#include <Math/MathUtils.h>

// TEMP
#include <vector>
#include <Graphics/IDrawable.h>
#include <Graphics/Model.h>
#include "DrawingRoutines.h"
extern std::vector<IDrawable*> debugDrawables;
extern Model *debugSphere;

LightsCollider::LightsCollider(const sm::Vec3 &position, const sm::Vec3 &direction) :
	m_position(position),
	m_direction(direction)
{
	SetColliderId(ColliderId_StreetLights);

	// TEMP
	//debugDrawables.push_back(this);
}

ColliderType LightsCollider::GetColliderType() const
{
	return ColliderType_StreetLights;
}

bool LightsCollider::CheckCollision(const Collider* collider, CollisionInfo& collisionInfo) const
{
	if (collider->GetColliderId() == ColliderId_Taxi)
		return false;

	sm::Vec3 directionToCollider = collider->GetPosition() - m_position;
	float distance = directionToCollider.GetLength();

	if (distance > 10.0f)
		return false;

	directionToCollider.Normalize();

	if (sm::Vec3::Dot(directionToCollider, m_direction) > 0.95f)
	{
		collisionInfo.m_colliderPosition = m_position;
		return true;
	}

	return false;
}

sm::Vec3 LightsCollider::GetPosition() const
{
	return m_position;
}

// TEMP
void LightsCollider::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(debugSphere->m_meshParts,
		sm::Matrix::TranslateMatrix(m_position) * sm::Matrix::ScaleMatrix(0.4f, 0.4f, 0.4f));

	DrawingRoutines::DrawWithMaterial(debugSphere->m_meshParts,
		sm::Matrix::TranslateMatrix(m_position + m_direction * 2) * sm::Matrix::ScaleMatrix(0.4f, 0.4f, 0.4f));
}
