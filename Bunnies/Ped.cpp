#include "Ped.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <FGraphicsOpengl2.h>
using namespace Tizen::Graphics::Opengl;

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
	sm::Matrix waveMatrix = sm::Matrix::IdentityMatrix();

	if (m_position != m_target)
	{
		m_direction = m_target - m_position;
		float distance = m_direction.GetLength();
		m_direction.Normalize();

		sm::Vec3 moveDelta = m_direction * 2.0f *seconds;

		if (moveDelta.GetLength() > distance)
			m_position = m_target;
		else
			m_position = m_position + moveDelta;

		float jumpVal = sinf(time * 30.0f) * 0.5f + 0.5f;
		float waveVal = sinf(time * 15.0f);

		waveMatrix =
			sm::Matrix::RotateAxisMatrix(waveVal * 0.15f, 0, 0, 1) *
			sm::Matrix::TranslateMatrix(0, jumpVal * 0.4f, 0);			
	}

	m_transform =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::CreateLookAt(m_direction, sm::Vec3(0, 1, 0)) *
		waveMatrix;
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
	m_target = position;

	m_isPassenger = false;

	m_model->SetMaterial(m_pedMaterial);
}

void Ped::SetToPassenger(const sm::Vec3 &tripDestination, float cash)
{
	m_positionBeforeApproaching = m_position;

	m_isPassenger = true;
	m_tripDestination = tripDestination;
	m_cash = cash;

	m_model->SetMaterial(m_passengerMaterial);
}

sm::Vec3 Ped::GetTripDestination() const
{
	return m_tripDestination;
}

bool Ped::IsPassenger() const
{
	return m_isPassenger;
}

void Ped::SetTarget(const sm::Vec3 &target)
{
	m_target = target;
}

void Ped::StartApproach()
{
}

void Ped::CancelApproach()
{
	m_target = m_positionBeforeApproaching;
}

bool Ped::IsTaxiInApproachRange(const sm::Vec3 &taxiPosition) const
{
	return (m_positionBeforeApproaching - taxiPosition).GetLength() <= 6.0f;
}
