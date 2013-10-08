#ifndef DRAWING_ROUTINES
#define DRAWING_ROUTINES

#include <Math/Vec3.h>
#include <Math/Matrix.h>

class Shader;
class Model;
class Texture;

class DrawingRoutines
{
public:
	static bool Initialize();

	static void DrawDiff(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);
	static void DrawingRoutines::DrawStreet(Model *model, Texture *diffuseTexture, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);
	static void DrawSkydome(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &projMatrix);
	static void DrawSprite(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);
	static void DrawGrass(Model *model, Texture *colorMapTex, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);

	static void SetLightPosition(const sm::Vec3 &lightPosition);
	static void SetOutlineWidth(float outlineWidth);
	static void SetProjectionMatrix(const sm::Matrix &projMatrix);

private:
	static Shader *m_celShadingShader;
	static Shader *m_celShadingMutatingShader;
	static Shader *m_outlineShader;
	static Shader *m_outlineMutatingShader;
	static Shader *m_skydomeShader;
	static Shader *m_diffTexShader;
	static Shader *m_diffShader;
	static Shader *m_grassShader;

	static float m_outlineWidth;
	static sm::Vec3 m_lightPosition;
	static sm::Matrix m_projMatrix;

	static Model *m_bloodParticleModel;
};

#endif // DRAWING_ROUTINES


