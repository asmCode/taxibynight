#pragma once

#include <Graphics/BoundingSphere.h>

namespace sm { class Vec3; }

class CollideObject
{
public:
	virtual const sm::Vec3& GetBoundingSphere() const = 0;
	virtual const sm::Vec3& GetPosition() const = 0;
};

