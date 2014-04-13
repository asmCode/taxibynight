#pragma once

#include <Math/Matrix.h>
#include <Math/Vec3.h>

class Animation;
class Model;
class Mesh;
class Texture;
class Material;
class StreetSegment;

class BonusStreetSymbol
{
public:
	static void Initialize();

	BonusStreetSymbol();
	~BonusStreetSymbol();

	void SetActive(const sm::Vec3& position, StreetSegment* streetSegment);
	void SetInactive();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);
	void DrawShadow(float time, float seconds);

	const sm::Vec3& GetPosition() const;
	const bool IsActive() const;

	const StreetSegment* GetStreetSegment() const;

private:
	bool m_isActive;
	sm::Vec3 m_position;
	sm::Matrix m_transform;

	static Model* m_model;

	float m_angle;
	float m_height;

	StreetSegment* m_streetSegment;
};

