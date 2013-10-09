#ifndef TAXI
#define TAXI

#include <Math/Matrix.h>

class Model;
class Texture;

class Taxi
{
public:
	Taxi();
	~Taxi();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void TurnLeft();
	void TurnRight();
	void Accelerate();

	const sm::Vec3& GetPosition() const;

private:
	sm::Matrix m_worldMatrix;

	bool m_isTurningLeft;
	bool m_isTurningRight;
	bool m_isAccelerating;

	Model *m_taxiModel;

	sm::Vec3 m_position;
	sm::Vec3 m_turnDirection; // normalized
	sm::Vec3 m_velocity;
};

#endif // TAXI

