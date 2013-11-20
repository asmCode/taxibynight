#include "StreetSegment.h"
#include "StreetPiece.h"
#include "Street.h"

#include <Utils/Randomizer.h>
#include <Math/MathUtils.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Utils/Log.h>
#include <assert.h>

StreetSegment::StreetSegment(const sm::Matrix &worldTransform, const sm::Vec3 &pivotPosition, StreetPiece *streetPiece)
{
	m_pivotPosition = pivotPosition;
	m_streetPiece = streetPiece;

	m_worldMatrix = worldTransform;
}

void StreetSegment::SetVisibility(bool visibility)
{
	m_isVisible = visibility;
}

bool StreetSegment::IsVisible() const
{
	return m_isVisible;
}

StreetPiece *StreetSegment::GetStreetPiece()
{
	return m_streetPiece;
}

const sm::Vec3& StreetSegment::GetPivotPosition() const
{
	return m_pivotPosition;
}

uint32_t StreetSegment::CoordX() const
{
	return (uint32_t)((m_pivotPosition.x + 5.0f) / 10.0f);
}

uint32_t StreetSegment::CoordY() const
{
	return (uint32_t)((m_pivotPosition.z + 5.0f) / 10.0f);
}

const sm::Matrix& StreetSegment::GetWorldTransform() const
{
	return m_worldMatrix;
}

StreetPath StreetSegment::GetRandomPathAtPosition(const sm::Vec3& position)
{
	static Randomizer random;

	float minDistance = 9999.0f;
	StreetPath *path = NULL;

	std::vector<StreetPath*> streetPathPool;

	// first iteration to find min distance
	for (unsigned int i = 0; i < m_streetPaths.size(); i++)
	{
		float distance = (m_streetPaths[i].GetBeginning() - position).GetLength();
		if (distance < minDistance)
			minDistance = distance;
	}

	// second iteration to get all points at the same position
	for (unsigned int i = 0; i < m_streetPaths.size(); i++)
	{
		float distance = (m_streetPaths[i].GetBeginning() - position).GetLength();
		if (MathUtils::Abs(distance - minDistance) < 1.0f)
			streetPathPool.push_back(&m_streetPaths[i]);
	}

	assert(streetPathPool.size() > 0);

	int index = random.GetInt(0, streetPathPool.size() - 1);

	Log::LogT("peeked path at index %d of %d paths", index, streetPathPool.size());

	return *streetPathPool[index];
}

void StreetSegment::InitializePaths()
{
	if (!m_streetPiece->HasRoad())
		return;

	int pathIndex = 0;
	int positionIndex = 0;

	StreetPath *path = NULL;

	while (true)
	{
		char name[10];
		sprintf(name, "path.%d.%d", pathIndex, positionIndex);

		Mesh *meshPoint = m_streetPiece->m_model->FindMesh(name);
		if (meshPoint == NULL && positionIndex == 0)
		{
			if (path != NULL)
				m_streetPaths.push_back(*path);

			break;
		}

		if (meshPoint == NULL)
		{
			m_streetPaths.push_back(*path);
			delete path;
			path = NULL;

			pathIndex++;
			positionIndex = 0;
		}
		else
		{
			if (path == NULL)
				path = new StreetPath();

			path->AddPosition((m_worldMatrix * m_streetPiece->GetTransform()) * (meshPoint->m_worldMatrix * sm::Vec3(0, 0, 0)));

			positionIndex++;
		}
	}

	for (int i = 0; i < m_streetPaths.size(); i++)
	{
		sm::Vec3 endPosition = m_streetPaths[i].GetEnd();

		sm::Vec3 compass = endPosition - m_pivotPosition;

		if (compass.x < 0 && MathUtils::Abs(compass.x) > MathUtils::Abs(compass.z))
			m_streetPaths[i].Initialize(Street::Instance->GetSegment(CoordX() - 1, CoordY()));
		else if (compass.x > 0 && MathUtils::Abs(compass.x) > MathUtils::Abs(compass.z))
			m_streetPaths[i].Initialize(Street::Instance->GetSegment(CoordX() + 1, CoordY()));
		else if (compass.z < 0 && MathUtils::Abs(compass.z) > MathUtils::Abs(compass.x))
			m_streetPaths[i].Initialize(Street::Instance->GetSegment(CoordX(), CoordY() - 1));
		else if (compass.z > 0 && MathUtils::Abs(compass.z) > MathUtils::Abs(compass.x))
			m_streetPaths[i].Initialize(Street::Instance->GetSegment(CoordX(), CoordY() + 1));
		else
		{
			assert(false);
		}
	}
}
