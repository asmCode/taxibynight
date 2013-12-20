#include "CollisionTester.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include <Math/MathUtils.h>
#include <stddef.h>
#include <assert.h>
#include <limits>

#include <vector>
extern std::vector<sm::Vec3> debugSpheres;

bool CollisionTester::TestCollision(RectCollider* c1, RectCollider* c2)
{
	assert(c1 != NULL);
	assert(c2 != NULL);

	c1->UpdateData();
	c2->UpdateData();

	sm::Vec2 *axises[] = 
	{
		&c1->m_axis1,
		&c1->m_axis2,
		&c2->m_axis1,
		&c2->m_axis2
	};

	float e1Min;
	float e1Max;
	float e2Min;
	float e2Max;
	float penetration;
	float minPenetration;
	sm::Vec2 mtv(0, 0);
		
	for (unsigned char i = 0; i < 4; i++)
	{
		GetProjectionBounds(*axises[i], c1->m_points, e1Min, e1Max);
		GetProjectionBounds(*axises[i], c2->m_points, e2Min, e2Max);

		if (!TestEdgeCollision(e1Min, e1Max, e2Min, e2Max, penetration))
			return false;
		else
		{
			if (MathUtils::Abs(penetration) < MathUtils::Abs(minPenetration))
			{
				minPenetration = penetration;
				mtv = *axises[i] * minPenetration;
			}
		}
	}

	debugSpheres.push_back(sm::Vec3(0, 0, 0));
	debugSpheres.push_back(sm::Vec3(mtv.x, mtv.y, 0));

	return true;
}

bool CollisionTester::TestCollision(RectCollider* c1, CircleCollider* c2)
{
	assert(c1 != NULL);
	assert(c2 != NULL);

	c1->UpdateData();
	c2->UpdateData();

	sm::Vec2 axises[6];

	CalcCircleAxises(c2->m_worldPosition, c1->m_points, axises);
	axises[4] = c1->m_axis1;
	axises[5] = c1->m_axis2;

	float e1Min;
	float e1Max;
	float e2Min;
	float e2Max;
	float penetration;
	float minPenetration;
	float circlePivotProjection;
	sm::Vec2 mtv(0, 0);

	for (unsigned char i = 0; i < 6; i++)
	{
		GetProjectionBounds(axises[i], c1->m_points, e1Min, e1Max);

		circlePivotProjection = sm::Vec2::Dot(axises[i], c2->m_worldPosition);
		e2Min = circlePivotProjection - c2->m_radius;
		e2Max = circlePivotProjection + c2->m_radius;

		if (!TestEdgeCollision(e1Min, e1Max, e2Min, e2Max, penetration))
			return false;
		else
		{
			if (MathUtils::Abs(penetration) < MathUtils::Abs(minPenetration))
			{
				minPenetration = penetration;
				mtv = axises[i] * minPenetration;
			}
		}
	}

	debugSpheres.push_back(sm::Vec3(0, 0, 0));
	debugSpheres.push_back(sm::Vec3(mtv.x, mtv.y, 0));

	return true;
}

void CollisionTester::GetProjectionBounds(
	const sm::Vec2& axis,
	const sm::Vec2 points[4],
	float &boundsMin,
	float &boundsMax)
{
	boundsMin = FLT_MAX;
	boundsMax = -FLT_MAX;

	for (unsigned char i = 0; i < 4; i++)
	{
		float edge = sm::Vec2::Dot(axis, points[i]);

		if (edge < boundsMin)
			boundsMin = edge;
		if (edge > boundsMax)
			boundsMax = edge;
	}
}

bool CollisionTester::TestEdgeCollision(
	float e1Min,
	float e1Max,
	float e2Min,
	float e2Max,
	float &penetrationValue)
{
	// edges are not overlapping
	if (e1Max < e2Min ||
		e2Max < e1Min)
		return false;

	float shiftLeft = MathUtils::Abs(e1Min - e2Max);
	float shiftRight = MathUtils::Abs(e2Min - e1Max);

	penetrationValue = MathUtils::Min(shiftLeft, shiftRight);

	// if first collider must be shifted to left, then notify it as a negative value
	if (shiftRight < shiftLeft)
		penetrationValue = -penetrationValue;

	return true;
}

void CollisionTester::CalcCircleAxises(
	const sm::Vec2& circlePosition,
	const sm::Vec2 rectCorners[4],
	sm::Vec2* axises)
{
	for (unsigned char i = 0; i < 4; i++)
		axises[i] = (circlePosition - rectCorners[i]).GetNormalized();
}
