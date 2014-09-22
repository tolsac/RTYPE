#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Entity.h"
#include "Player.h"
#include "Missile.h"
#include "Bullet.h"
#include "SphereOfDeath.h"
#include "Enemy.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void addEntity(int id, int idType, float posX, float posY, sf::Image *image);
	void deleteEntity(int id);
	void moveEntity(int id, float posX, float posY);
	std::map<int, Entity *>& getEntities();
private:
	std::map<int, Entity *> myEntities;
};

#endif /*__ENTITYMANAGER_H__*/