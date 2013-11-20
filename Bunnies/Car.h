#pragma once

#include "StreetPath.h"
#include <Math/Vec3.h>
#include <Math/Matrix.h>

class Car
{
public:
	Car();
	~Car();

	void Update(float time, float seconds);

	void SetActive(const sm::Vec3 &initialPosition);
	void SetInactive();
	bool IsActive() const;

	const sm::Matrix& GetWorldMatrix() const;

private:
	bool m_isActive;

	StreetPath m_streetPath;

	sm::Matrix m_worldMatrix;

	float m_acceleration;
	sm::Vec3 m_destination;
	sm::Vec3 m_position;

	float m_speed;

	float m_maxSpeed;

	bool CanDrive();
	void DriveToDestination(float seconds);
	void GetNewDestination(bool atTheEdge);
};

