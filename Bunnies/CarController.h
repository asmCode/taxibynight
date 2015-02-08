#pragma once

#include <Math/Matrix.h>

class CarPhysics;

class CarController
{
private:
	enum BreakPedalFunction
	{
		BreakPedalFunction_None,
		BreakPedalFunction_Break,
		BreakPedalFunction_Reverse
	};

public:
	enum SteerDirection
	{
		Steer_Left,
		Steer_Right,
		Steer_None
	};

	CarController();
	virtual ~CarController();

	void Initialize();
	void SetParameters(
		float enginePower,
		float frontAxisDistance,
		float rearAxisDistance,
		float totalMass,
		float traction);

	void Update(float deltaTime);

	void Steer(SteerDirection steer);
	void Accelerate(bool press);
	void Break(bool press);

	float GetSpeed() const;
	sm::Matrix GetTransform() const;
	sm::Vec3 GetPosition() const;
	sm::Vec3 GetDirection() const;

public:
	CarPhysics* m_carPhysics;

private:
	static float SteerAngleLimit;
	static float SteerSpeed;
	static float SteerBackSpeed;

	void UpdatePedals(float deltaTime);
	void UpdateSteering(float deltaTime);

	BreakPedalFunction m_breakPedalFunction;

	bool m_isBreakPressed;
	bool m_isAccelerationPressed;
	SteerDirection m_steerDirection;
	float m_steerAngle;
};
