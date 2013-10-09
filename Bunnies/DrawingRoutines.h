#ifndef DRAWING_ROUTINES
#define DRAWING_ROUTINES

#include <Math/Vec3.h>
#include <Math/Matrix.h>
#include <vector>

class Shader;
class Model;
class MeshPart;
class Texture;
class Material;

class DrawingRoutines
{
public:
	static bool Initialize();

	static void DrawDiff(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);
	static void DrawStreet(Model *model, Texture *diffuseTexture, const sm::Matrix &worldMatrix);
	static void DrawWithMaterial(std::vector<MeshPart*> &meshParts, const sm::Matrix &worldMatrix);
	static void DrawSkydome(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &projMatrix);
	static void DrawSprite(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);
	static void DrawGrass(Model *model, Texture *colorMapTex, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix);

	static void SetLightPosition(const sm::Vec3 &lightPosition);
	static void SetEyePosition(const sm::Vec3 &eyePosition);
	static void SetOutlineWidth(float outlineWidth);
	static void SetProjectionMatrix(const sm::Matrix &projMatrix);
	static void SetViewMatrix(const sm::Matrix &viewMatrix);

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
	static sm::Vec3 m_eyePosition;
	static sm::Matrix m_projMatrix;
	static sm::Matrix m_viewMatrix;
	static sm::Matrix m_viewProjMatrix;

	static Model *m_bloodParticleModel;

	static bool SetupShader(Material *material, MeshPart *meshPart, const sm::Matrix &worldatrix);
};

#endif // DRAWING_ROUTINES


