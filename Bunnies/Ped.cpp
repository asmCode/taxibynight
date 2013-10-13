#include "Ped.h"
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

Ped::Ped()
{
	Content *content = InterfaceProvider::GetContent();

	m_model = content->Get<Model>("passenger");
	assert(m_model != NULL);

	m_transform = sm::Matrix::IdentityMatrix();
	m_direction.Set(0, 0, -1);
}

Ped::~Ped()
{
}

void Ped::Update(float time, float seconds)
{
	m_transform =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_direction, sm::Vec3(0, 1, 0));
}

void Ped::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(m_model->m_meshParts, m_transform);
}

const sm::Vec3& Ped::GetPosition() const
{
	return m_position;
}

void Ped::ResetPosition(const sm::Vec3 position)
{
	m_position = position;
}
