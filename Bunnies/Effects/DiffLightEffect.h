#ifndef DIFF_LIGHT_EFFECT
#define DIFF_LIGHT_EFFECT

#include <Math/Matrix.h>
#include <Math/Vec3.h>
#include <Core/stdint.h>

class Shader;
class Texture;

class DiffLightEffect
{
public:
	DiffLightEffect(Shader* shader);
	
	void Begin();
	
	void SetWorldMatrix(const sm::Matrix& worldMatrix);
	void SetViewProjMatrix(const sm::Matrix& viewProjMatrix);
	void SetLightPosition(const sm::Vec3& lightPosition);
	void SetTexture(Texture* texture);
	
private:
	Shader* m_shader;
	
	sm::Matrix m_worldMatrix;
	sm::Matrix m_viewProjMatrix;
	sm::Vec3 m_lightPosition;
	Texture* m_texture;
	
	uint32_t m_worldMatrixLocation;
	uint32_t m_viewProjMatrixLocation;
	uint32_t m_lightPositionLocation;
	uint32_t m_textureLocation;
};

#endif

