#include "Camera.h"

namespace sm
{

Camera::Camera() :
		m_position(0, 0, 0),
		m_lookDirection(0, 0, -1),
		m_roll(0.0f),
		m_needUpdate(true)
{
}

Camera::~Camera()
{
}

const Matrix& Camera::GetViewMatrix()
{
	if (m_needUpdate)
		RecalcViewMatrix();

	return m_viewMatrix;
}


const Vec3& Camera::GetPosition() const
{
	return m_position;
}

const Vec3& Camera::GetLookDirection() const
{
	return m_lookDirection;
}

void Camera::SetPosition(const Vec3& position)
{
	m_position = position;

	m_needUpdate = true;
}

void Camera::SetLookDirection(const Vec3& direction)
{
	m_lookDirection = direction;

	m_needUpdate = true;
}

void Camera::SetRoll(float roll)
{
	m_roll = roll;

	m_needUpdate = true;
}

void Camera::RecalcViewMatrix()
{
	//Vec3 up = Matrix::RotateAxisMatrix(m_roll, m_lookDirection) * Vec3(0, 1, 0);
	//Vec3 up = Matrix::RotateAxisMatrix(m_roll, Vec3(m_lookDirection.x, 0, m_lookDirection.z).GetNormalized()) * Vec3(0, 1, 0);
	Vec3 up(0, 1, 0);

	m_viewMatrix =
		Matrix::CreateLookAt2(m_lookDirection.GetReversed(), up) *
		Matrix::TranslateMatrix(m_position.GetReversed());

	m_needUpdate = false;
}

} // namespace sm
