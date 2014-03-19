#ifndef CAMERA_H_
#define CAMERA_H_

#include <Math/Vec3.h>
#include <Math/Matrix.h>

namespace sm
{

class Camera
{
public:
	Camera();
	virtual ~Camera();

	const Matrix& GetViewMatrix();
	const Vec3& GetPosition() const;
	const Vec3& GetLookDirection() const;

	virtual void SetPosition(const Vec3& position);
	virtual void SetLookDirection(const Vec3& direction);
	virtual void SetRoll(float roll);

protected:
	Vec3 m_position;
	Vec3 m_lookDirection;
	float m_roll;

	bool m_needUpdate;

	Matrix m_viewMatrix;

	void RecalcViewMatrix();
};

} // namespace sm

#endif // CAMERA_H_
