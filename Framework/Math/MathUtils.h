#pragma once
#ifndef _MATHUTILS_
#define _MATHUTILS_

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

class MathUtils
{
private:
	static void GetDotsAndLengths(sm::Vec3 *points, float *dots, float *lengths)
	{
		for (int i = 0; i < 4; i++)
		{
			sm::Vec3 v1 = points[(4 + (i - 1)) % 4] - points[i]; // one left
			sm::Vec3 v2 = points[(i + 1) % 4] - points[i]; // one right

			lengths[i] = v2.GetLength();

			v1.Normalize();
			v2.Normalize();

			dots[i] = sm::Vec3::Dot(v1, v2);
		}
	}

public:
	static float GetDistanceFromSegment(sm::Vec3 a, sm::Vec3 b, sm::Vec3 p)
	{
		sm::Vec3 ab = b - a;
		sm::Vec3 ap = p - a;

		sm::Vec3 abn = ab;
		abn.Normalize();

		float d = sm::Vec3::Dot(abn, ap);

		sm::Vec3 h = a + (abn * d);

		sm::Vec3 ha = a - h;
		sm::Vec3 hb = b - h;

		// TODO: do poprawki! galon pokazal lepszy sposob
		if (sm::Vec3::Dot(ha, hb) < 0.0f) // czy punkt miesci sie w odcinku?
		{
			sm::Vec3 ph = h - p;
			return ph.GetLength();
		}
		else // jesli nie, to szukamy odleglosci od krancow odcinka i zwracamy mniejsza odleglosc
		{
			sm::Vec3 bp = p - b;
			float l1 = bp.GetLength();
			float l2 = ap.GetLength();

			if (l1 < l2)
				return l1;
			else
				return l2;
		}
	}

	static float GetDistanceFromLine(sm::Vec3 a, sm::Vec3 b, sm::Vec3 p)
	{
		sm::Vec3 ab = b - a;
		sm::Vec3 ap = p - a;

		sm::Vec3 abn = ab;
		abn.Normalize();

		float d = sm::Vec3::Dot(abn, ap);

		sm::Vec3 h = a + (abn * d);

		sm::Vec3 ph = h - p;
		return ph.GetLength();
	}

	static bool IsPointInTriangle(sm::Vec3 a, sm::Vec3 b, sm::Vec3 c, sm::Vec3 p)
	{
		sm::Vec3 ab = b - a;
		sm::Vec3 ac = c - a;
		sm::Vec3 ap = p - a;

		sm::Vec3 ba = a - b;
		sm::Vec3 bc = c - b;
		sm::Vec3 bp = p - b;

		return
			sm::Vec3::Dot(ab * ac, ab * ap) >= 0 &&
			sm::Vec3::Dot(ac * ab, ac * ap) >= 0 &&
			sm::Vec3::Dot(bc * ba, bc * bp) >= 0;
	}

	static bool IsPointInTriangle(sm::Vec2 a, sm::Vec2 b, sm::Vec2 c, sm::Vec2 p)
	{
		return IsPointInTriangle(
			sm::Vec3(a.x, a.y, 0), sm::Vec3(b.x, b.y, 0), sm::Vec3(c.x, c.y, 0), sm::Vec3(p.x, p.y, 0));
	}

	template <typename Vec3Collection>
	static bool IsPointInConvexSet(sm::Vec3 point, Vec3Collection convexSet, int convexSetPointsCount)
	{
		if (convexSetPointsCount < 3)
			return false;

		float angle = 0.0f;

		for (int i = 0; i < convexSetPointsCount; i++)
		{
			angle += sm::Vec3::GetAngle(
				(convexSet[i] - point).GetNormalized(),
				(convexSet[(i + 1) % convexSetPointsCount] - point).GetNormalized());
		}

		return angle > 6.2f;
	}

	template <typename Vec3Collection>
	static float GetConvexSetArea(Vec3Collection convexSet, int convexSetPointsCount)
	{
		if (convexSetPointsCount < 3)
			return 0.0f;

		float area = 0.0f;
		sm::Vec3 point = GetAvgVector(convexSet, convexSetPointsCount);

		for (int i = 0; i < convexSetPointsCount; i++)
			area += GetTriangleArea(point, convexSet[i], convexSet[(i + 1) % convexSetPointsCount]);

		return area;
	}

	static float GetTriangleArea(sm::Vec3 a, sm::Vec3 c, sm::Vec3 b)
	{
		return ((c - a) * (b - a)).GetLength() / 2.0f;
	}

	static float GetQuadArea(sm::Vec3 a, sm::Vec3 b, sm::Vec3 c, sm::Vec3 d)
	{
		return GetTriangleArea(a, b, c) + GetTriangleArea(c, d, a);
	}

	template <typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	static inline float Sign(const float &v)
	{
		if (v > 0.0f) return 1.0f;
		if (v < 0.0f) return -1.0f;
		return 0.0f;
	}

	template <typename T>
	static inline T Clamp(const T &v, const T &_min, const T &_max)
	{
		return Max(Min(v, _max), _min);
	}

	template <typename T>
	static inline T Abs(const T &v)
	{
		return v >= 0 ? v : -v;
	}

	static const float PI;
	static const float PI2;
	static const float PI4;
	static const float Deg2Rad;
};

#endif
