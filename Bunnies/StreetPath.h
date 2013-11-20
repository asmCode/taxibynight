#pragma once

#include <Math/Vec3.h>
#include <vector>

class StreetSegment;

class StreetPath
{
public:
	StreetPath();

	void Initialize(StreetSegment *continousStreetSegment);
	void Rewind();
	sm::Vec3 GetNextPosition();
	sm::Vec3 GetBeginning();
	sm::Vec3 GetEnd();
	bool IsAtTheEnd() const;
	void AddPosition(const sm::Vec3& position);
	StreetSegment* GetContinousSegment() const;

private:
	int m_index;

	std::vector<sm::Vec3> m_positions;

	StreetSegment *m_continousStreetSegment;
};

