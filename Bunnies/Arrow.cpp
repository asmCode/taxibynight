#include "Arrow.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

Arrow::Arrow()
{
	Content *content = InterfaceProvider::GetContent();

	m_model = content->Get<Model>("arrow");
	assert(m_model != NULL);

	m_transform = sm::Matrix::IdentityMatrix();
	m_direction.Set(0, 0, -1);
}

Arrow::~Arrow()
{
}

void Arrow::Update(float time, float seconds)
{
	m_direction = sm::Vec3(1, 0, 1).GetNormalized();

	m_transform =
		sm::Matrix::CreateLookAt(m_direction, sm::Vec3(0, 1, 0)) *
		sm::Matrix::ScaleMatrix(0.4f, 0.4f, 0.4f);
}

void Arrow::Draw(float time, float seconds)
{
	float width = (float)Environment::GetInstance()->GetScreenWidth();
	float height = (float)Environment::GetInstance()->GetScreenHeight();

	float arrowWidth = width * 0.1f;

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport((width - arrowWidth) / 2, height - arrowWidth, arrowWidth, arrowWidth);

	sm::Vec3 camPosition(0, 12, -6);
	sm::Vec3 camLook = (camPosition - (sm::Vec3(0, 0, 0))).GetNormalized();
	sm::Matrix viewMatrix =
		sm::Matrix::TranslateMatrix(camPosition) *
		sm::Matrix::CreateLookAt2(camLook, sm::Vec3(0, 1, 0));

	viewMatrix = viewMatrix.GetInversed();

	DrawingRoutines::SetViewMatrix(viewMatrix);
	DrawingRoutines::SetProjectionMatrix(sm::Matrix::PerspectiveMatrix(45.0f, 1, 0.1f, 100.0f));
	DrawingRoutines::SetLightPosition(camPosition);
	DrawingRoutines::SetEyePosition(camPosition);
	DrawingRoutines::DrawWithMaterial(m_model->m_meshParts, m_transform);

	glViewport(0, 0, Environment::GetInstance()->GetScreenWidth(), Environment::GetInstance()->GetScreenHeight());
}

void Arrow::SetDirection(const sm::Vec3 &direction)
{
	m_direction = direction;
}

