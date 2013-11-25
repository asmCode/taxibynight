#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>

class IColliderHolder;
class Collider;
class CollisionInfo;

class CollisionManager
{
public:
	static CollisionManager* m_instance;

	~CollisionManager();

	static CollisionManager* GetInstance();

	void AddColliderHolder(IColliderHolder* colliderHolder);
	bool CheckCollision(IColliderHolder *collisionHolder, CollisionInfo& collisionInfo, Collider *exclude = NULL);
	bool CheckCollision(const Collider *collider, CollisionInfo& collisionInfo, Collider *exclude = NULL);

private:
	CollisionManager();

	std::vector<IColliderHolder*> m_colliderHolders;
};

#endif // !COLLISION_MANAGER
