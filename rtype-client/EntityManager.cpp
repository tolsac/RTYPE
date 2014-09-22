#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

void EntityManager::addEntity(int id, int idType, float posX, float posY, sf::Image *image)
{
  std::cout << "je rajoute un entity" << std::endl;
  Entity *e;
  if (idType == 0)
    e = new Player(id, idType, posX, posY, image);
  else if (idType == 1)
    e = new Missile(id, idType, posX, posY, image);
  else if (idType == 2)
    e = new Bullet(id, idType, posX, posY, image);
  else if (idType == 3)
	  e = new SphereOfDeath(id, idType, posX, posY, image);
  else if (idType == 4)
	  e = new Enemy(id, idType, posX, posY, image);
  else
    {
      std::cout << "idType not found == " << idType << std::endl;
      return;
    }
  this->myEntities[id] = e;
}

void EntityManager::deleteEntity(int id)
{
	this->myEntities.erase(id);
}

void EntityManager::moveEntity(int id, float posX, float posY)
{
  std::cout << "*********** MOVE ENTITY " << id << std::endl;
  if (!this->myEntities.find(id)->second == NULL)
    {
      this->myEntities[id]->setPosX(posX);
      this->myEntities[id]->setPosY(posY);
      this->myEntities[id]->setPosSprite(posX, posY);
		/*
      this->myEntities[id]->setDestX(posX);
      this->myEntities[id]->setDestY(posY);
      //this->myEntities[id]->setPosSprite(posX, posY);
	  */
    }
}

std::map<int, Entity *>& EntityManager::getEntities()
{
	return (this->myEntities);
}
