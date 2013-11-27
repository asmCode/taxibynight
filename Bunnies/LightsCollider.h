#ifndef LIGHTS_COLLIDER
#define LIGHTS_COLLIDER

#include "Collider.h"
#include <Math/Vec3.h>
#include <Math/Matrix.h>

// TEMO
#include <Graphics/IDrawable.h>

class LightsCollider : public Collider, public IDrawable
{
public:
	LightsCollider(const sm::Vec3 &position, const sm::Vec3 &direction);

	ColliderType GetColliderType() const;

	bool CheckCollision(const Collider* collider, CollisionInfo& collisionInfo) const;

	sm::Vec3 GetPosition() const;

	void Draw(float time, float seconds);

private:
	sm::Vec3 m_position;
	sm::Vec3 m_direction;
};

#endif // LIGHTS_COLLIDER

