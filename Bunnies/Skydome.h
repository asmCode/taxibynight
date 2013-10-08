#pragma once

#include <Math/Matrix.h>

class Model;

class Skydome
{
public:
	Skydome();
	~Skydome(void);

	void SetViewMatrix(const sm::Matrix &viewMatrix);
	void SetProjMatrix(const sm::Matrix &projMatrix);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

private:
	Model *m_skydomeModel;

	sm::Matrix m_viewMatrix;
	sm::Matrix m_projMatrix;
};

