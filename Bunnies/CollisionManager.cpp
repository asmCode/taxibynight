#include "CollisionManager.h"
#include "Collider.h"
#include "IColliderHolder.h"
#include <stddef.h>

CollisionManager* CollisionManager::m_instance;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new CollisionManager();

	return m_instance;
}

void CollisionManager::AddColliderHolder(IColliderHolder* colliderHolder)
{
	m_colliderHolders.push_back(colliderHolder);
}

bool CollisionManager::CheckCollision(IColliderHolder *collisionHolder)
{
	const Collider* sourceCollider = collisionHolder->GetCollider();
	assert(sourceCollider != NULL);

	for (size_t i = 0; i < m_colliderHolders.size(); i++)
	{
		const Collider* destinationCollider = m_colliderHolders[i]->GetCollider();
		assert(destinationCollider != NULL);

		if (sourceCollider == destinationCollider)
			continue;

		if (sourceCollider->CheckCollision(destinationCollider))
			return true;
	}

	return false;
}
