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

	m_pedMaterial = content->Get<Material>("ped");
	assert(m_pedMaterial != NULL);

	m_passengerMaterial = content->Get<Material>("passenger");
	assert(m_passengerMaterial != NULL);

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
	if (IsPassenger())
		m_model->SetMaterial(m_passengerMaterial);
	else
		m_model->SetMaterial(m_pedMaterial);

	DrawingRoutines::DrawWithMaterial(m_model->m_meshParts, m_transform);
}

const sm::Vec3& Ped::GetPosition() const
{
	return m_position;
}

void Ped::ResetPosition(const sm::Vec3 position)
{
	m_position = position;

	m_isPassenger = false;

	m_model->SetMaterial(m_pedMaterial);
}

void Ped::SetToPassenger(const sm::Vec3 &tripDestination, float cash)
{
	m_isPassenger = true;
	m_tripDestination = tripDestination;
	m_cash = cash;

	m_model->SetMaterial(m_passengerMaterial);
}

bool Ped::IsPassenger() const
{
	return m_isPassenger;
}

