#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>

class IColliderHolder;

class CollisionManager
{
public:
	static CollisionManager* m_instance;

	~CollisionManager();

	static CollisionManager* GetInstance();

	void AddColliderHolder(IColliderHolder* colliderHolder);
	bool CheckCollision(IColliderHolder *collisionHolder);

private:
	CollisionManager();

	std::vector<IColliderHolder*> m_colliderHolders;
};

#endif // !COLLISION_MANAGER
