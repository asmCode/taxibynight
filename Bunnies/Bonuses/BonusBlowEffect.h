#ifndef BONUS_BLOW_EFFECT
#define BONUS_BLOW_EFFECT

#include <Math/Matrix.h>
#include <Math/Vec4.h>

class Shader;
class Texture;
class Material;
template <typename T> class TCBInterpolator;

class BonusBlowEffect
{
public:
	static void Initialize();

	BonusBlowEffect();
	~BonusBlowEffect();

	void Update(float time, float seconds, const sm::Matrix viewProjMatrix);
	void Draw(float time, float seconds);

	void SetPosition(const sm::Vec3 &position);

	void Blow();

private:
	bool m_isActive;

	sm::Matrix m_transform;
	sm::Matrix m_baseTransform;
	sm::Matrix m_viewProjMatrix;

	sm::Vec3 m_position;

	float m_effectTime;
	float m_maxScale;

	sm::Vec4 m_color;

	static Texture* m_texture;
	static Shader* m_spriteShader;
	static TCBInterpolator<float>* m_transparencyCurve;
	static TCBInterpolator<float>* m_scaleCurve;
};

#endif // BONUS_BLOW_EFFECT

