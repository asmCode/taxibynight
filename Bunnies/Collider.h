#ifndef COLLIDER
#define COLLIDER

#include "ColliderType.h"
#include "ColliderId.h"
#include <Math/Matrix.h>

class CollisionInfo;

class Collider
{
public:
	Collider();
	virtual ~Collider() {}

	void SetTransform(const sm::Matrix& transform);
	void SetColliderId(ColliderId colliderId);

	virtual ColliderType GetColliderType() const = 0;
	virtual ColliderId GetColliderId() const;

	virtual bool CheckCollision(const Collider* collider, CollisionInfo& collisionInfo) const = 0;
	virtual sm::Vec3 GetPosition() const = 0;

protected:
	sm::Matrix m_transform;
	sm::Matrix m_transformInverted;

	ColliderId m_colliderId;
};

#endif // !COLLIDER
