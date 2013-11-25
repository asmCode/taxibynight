#ifndef COLLIDER
#define COLLIDER

#include "ColliderType.h"
#include <Math/Matrix.h>

class Collider
{
public:
	virtual ~Collider() {}

	void SetTransform(const sm::Matrix& transform);

	virtual ColliderType GetColliderType() const = 0;

	virtual bool CheckCollision(const Collider* collider) const = 0;
	virtual sm::Vec3 GetPosition() const = 0;

protected:
	sm::Matrix m_transform;
	sm::Matrix m_transformInverted;
};

#endif // !COLLIDER
