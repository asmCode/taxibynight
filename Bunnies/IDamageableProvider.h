#pragma once

#include <Math/Vec3.h>
#include <stdint.h>

class IDamageable;

class IDamageableProvider
{
public:
	virtual void GetAllDamageables(IDamageable **objects, uint32_t &count) = 0;

	virtual void GetDamageablesInCone(
		IDamageable **objects,
		uint32_t &count,
		const sm::Vec3 &coneTop,
		const sm::Vec3 &coneTarget,
		float cosOfAngle) = 0; // cosine of angle

	virtual void GetDamageablesInRange(
		IDamageable **objects,
		uint32_t &count,
		const sm::Vec3 &position,
		float range) = 0;
};

