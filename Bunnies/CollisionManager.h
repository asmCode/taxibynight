#pragma once

#include <vector>

class CollideObject;

class CollisionManager
{
public:
	CollisionManager(void);
	~CollisionManager(void);

	void AddCollideObject(CollideObject *collideObject);
	void RemoveCollideObject(CollideObject *collideObject);

	void CheckCollision(
		bool &collisionOccured,
		CollideObject *collideObject);

private:
	std::vector<CollideObject*> m_objects;
};

