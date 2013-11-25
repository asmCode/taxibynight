#ifndef LIGHTS_COLLIDER
#define LIGHTS_COLLIDER

#include "Collider.h"
#include <Math/Vec3.h>
#include <Math/Matrix.h>

class LightsCollider : public Collider
{
public:
	LightsCollider(const sm::Vec3 &position, const sm::Vec3 &direction);

	ColliderType GetColliderType() const;

	bool CheckCollision(const Collider* collider) const;

	sm::Vec3 GetPosition() const;

private:
	sm::Vec3 m_position;
	sm::Vec3 m_direction;
};

#endif // LIGHTS_COLLIDER

