#ifndef PED
#define PED

#include <Math/Matrix.h>

class Animation;
class Model;
class Mesh;
class Texture;

class Ped
{
public:
	Ped();
	~Ped();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void ResetPosition(const sm::Vec3 position);
	const sm::Vec3& GetPosition() const;

private:
	sm::Matrix m_transform;

	Model *m_model;

	Animation *m_walkAnim;
	Animation *m_waveAnim;
	Animation *m_getInAnim;
	Animation *m_getOutAnim;

	sm::Vec3 m_position;
	sm::Vec3 m_direction;
};

#endif // PED

