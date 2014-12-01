#pragma once

#include <Math/Matrix.h>
#include "Camera.h"	

class Model;
class Mesh;
class Texture;
class Material;

class GuiCar
{
public:
	GuiCar();
	~GuiCar();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	sm::Matrix m_worldMatrix;

	void SetCameraPosition(const sm::Vec3& position);
	void SetCameraLookAt(const sm::Vec3& lookAt);

private:
	Model *m_carModel;
	Model *m_shadow;

	sm::Camera m_camera;
};

