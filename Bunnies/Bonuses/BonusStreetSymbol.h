#pragma once

#include <Math/Matrix.h>
#include <Math/Vec3.h>

class Animation;
class Model;
class Mesh;
class Texture;
class Material;

class BonusStreetSymbol
{
public:
	static void Initialize();

	BonusStreetSymbol();
	~BonusStreetSymbol();

	void SetPosition(const sm::Vec3& position);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);
	void DrawShadow(float time, float seconds);

private:
	sm::Vec3 m_position;

	static Model* m_model;
};

