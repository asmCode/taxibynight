#include "Matrix.h"

namespace sm
{

Matrix Matrix::CreateLookAt2(const sm::Vec3 &direction, const sm::Vec3 &up)
{
	sm::Matrix rot = sm::Matrix::IdentityMatrix();

	sm::Vec3 right = (direction * up).GetNormalized();
	sm::Vec3 yAxis = (right * direction).GetNormalized();

	rot.a[0] = right.x;
	rot.a[1] = right.y;
	rot.a[2] = right.z;

	rot.a[4] = yAxis.x;
	rot.a[5] = yAxis.y;
	rot.a[6] = yAxis.z;

	rot.a[8] = direction.x;
	rot.a[9] = direction.y;
	rot.a[10] = direction.z;

	return rot;
}

}

