#pragma once

#include "Camera.h"	
#include <Math/Matrix.h>
#include <string>

class Model;
class Mesh;
class Texture;
class Material;

class GuiCar
{
public:
	GuiCar(const std::string& carsPath);
	~GuiCar();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	sm::Matrix m_worldMatrix;

	void SetCameraPosition(const sm::Vec3& position);
	void SetCameraLookAt(const sm::Vec3& lookAt);

	void UnloadAll();
	void LoadCar(const std::string& carId);
	void LoadDecal(const std::string& decalId);
	void Show(bool show);

private:
	Model *m_carModel;
	Texture* m_decalTexture;
	Material* m_commonCarMaterial;
	Model *m_shadow;

	std::string m_carsPath;

	std::string m_currentCarId;
	std::string m_currentDecalId;

	bool m_show;

	sm::Camera m_camera;

	void UnloadCar();
	void UnloadDecal();
};

