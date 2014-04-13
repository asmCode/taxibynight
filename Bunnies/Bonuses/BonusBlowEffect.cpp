#include "BonusBlowEffect.h"
#include "../DrawingRoutines.h"
#include "../InterfaceProvider.h"
#include "../Billboard.h"
#include "../Environment.h"

#include <Graphics/Interpolators/TCBInterpolator.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

Texture* BonusBlowEffect::m_texture;
Shader* BonusBlowEffect::m_spriteShader;
TCBInterpolator<float>* BonusBlowEffect::m_transparencyCurve;
TCBInterpolator<float>* BonusBlowEffect::m_scaleCurve;

void BonusBlowEffect::Initialize()
{
	Content *content = InterfaceProvider::GetContent();

	m_texture = content->Get<Texture>("bonus_blow");
	assert(m_texture != NULL);

	m_spriteShader = content->Get<Shader>("Sprite2");
	assert(m_spriteShader != NULL);
	m_spriteShader->BindVertexChannel(0, "a_position");
	m_spriteShader->LinkProgram();

	m_scaleCurve = new TCBInterpolator<float>();
	m_scaleCurve->AddKeyframe(0.0f, 0.0f, false);
	m_scaleCurve->AddKeyframe(0.25f, 0.8f, false);
	m_scaleCurve->AddKeyframe(0.5f, 1.0f, false);

	m_transparencyCurve = new TCBInterpolator<float>();
	m_transparencyCurve->AddKeyframe(0.0f, 1.0f, false);
	m_transparencyCurve->AddKeyframe(0.25f, 0.8f, false);
	m_transparencyCurve->AddKeyframe(0.5f, 0.0f, false);
}

BonusBlowEffect::BonusBlowEffect()
{
	m_isActive = false;

	m_baseTransform = sm::Matrix::RotateAxisMatrix(-MathUtils::PI2, 1, 0, 0);
	m_transform = sm::Matrix::IdentityMatrix();

	//m_color.Set(1, 0.7f, 0, 0.8f);
	m_color.Set(0.5f, 0.5f, 0.5f, 0.8f);
	m_effectTime = 0.0f;
	m_maxScale = 8.0f;
}

BonusBlowEffect::~BonusBlowEffect()
{
}

void BonusBlowEffect::Update(float time, float seconds, const sm::Matrix viewProjMatrix)
{
	if (!m_isActive)
		return;

	m_effectTime += seconds;

	float scaleVal;
	m_scaleCurve->GetValue(m_effectTime, scaleVal);
	scaleVal *= m_maxScale;

	m_transparencyCurve->GetValue(m_effectTime, m_color.w);

	m_transform =
		viewProjMatrix *
		sm::Matrix::TranslateMatrix(m_position) *
		m_baseTransform *
		sm::Matrix::ScaleMatrix(scaleVal, scaleVal, scaleVal);
}

void BonusBlowEffect::Draw(float time, float seconds)
{
	if (!m_isActive)
		return;

	m_spriteShader->UseProgram();
	m_spriteShader->SetMatrixParameter("u_mvp", m_transform);
	m_spriteShader->SetTextureParameter("u_tex", 0, m_texture->GetId());
	m_spriteShader->SetParameter("u_color", m_color);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	Billboard::Setup();
	Billboard::Draw();
	Billboard::Clean();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void BonusBlowEffect::Blow()
{
	m_isActive = true;
	m_effectTime = 0.0f;
}

void BonusBlowEffect::SetPosition(const sm::Vec3 &position)
{
	m_position = position;
}

