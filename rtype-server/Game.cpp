#include	"Game.h"
#include	"LockGuard.h"
#include	"Rect.hpp"
#include	"GameObjectFactory.h"
#include	"ClientBehaviour.h"
#include	"Logger.h"
#include	"Room.h"
#include	"Convert.hh"
#include	"Connexion.h"
#include	"Singleton.hpp"
#include	"NetworkManager.h"

#include	<sstream>

Game::Game(Room* room)
	:	_room(room),
		_currentId(0)
{
	this->_map = new Map(this);
	Logger::logInfo("created game for room " + room->getName());
}

Game::~Game()
{
	Logger::logInfo("deleted game for room " + this->_room->getName());
	for (auto it = this->_entities.begin(); it != this->_entities.end(); ++it)
	{
		(*it)->destroy();
		delete (*it);
	}
}

bool		Game::_isColliding(GameObject* g1, GameObject* g2)
{
	/* filling bounding box 1 */
	epi::Rect4f		jbb1;
	jbb1.x = g1->getPosition().x +  g1->getBoundingBox().x;
	jbb1.y = g1->getPosition().y + g1->getBoundingBox().y;
	jbb1.width = g1->getBoundingBox().width;
	jbb1.height = g1->getBoundingBox().height;

	/* filling bounding box 2 */
	epi::Rect4f		jbb2;
	jbb2.x = g2->getPosition().x +  g2->getBoundingBox().x;
	jbb2.y = g2->getPosition().y + g2->getBoundingBox().y;
	jbb2.width = g2->getBoundingBox().width;
	jbb2.height = g2->getBoundingBox().height;

	if (jbb1.inter(jbb2))
	{
		//send message to network
		return true;
	}
	else
	{
		return false;
	}
}

void		Game::refreshEntity(GameObject* go, bool checkCollision)
{
	if (checkCollision)
	{
		this->checkCollision(go);
	}
	//send message to network
	this->_broadcastPacket(PacketFactory::createPacketMoveEntity(go->getId(), go->getPosition().x, go->getPosition().y, -1), true);
}


void		Game::checkCollision(GameObject* go)
{
	//tmp : std::list version

	for (auto it = this->_entities.begin(); it != this->_entities.end(); ++it)
	{
		if ((*it) != go)
		{
			if (this->_isColliding(go, (*it)))
			{
				go->onCollision((*it));
				(*it)->onCollision(go);
			}
		}
	}


	//soon : QuadTree version 
}

int			Game::_generateId()
{
	return this->_currentId++;
}

Room*		Game::getRoom() const
{
	return this->_room;
}

float		Game::getElapsedTime() const
{
	return this->_clock.getElapsedTime();
}


void		Game::init()
{
	this->_map->init();

	int	i = 0;
	for (auto it = this->_clients.begin(); it != this->_clients.end(); ++it, ++i)
	{
		int		posx = 50;
		int		posy = ((this->_sizey - 100) / this->_clients.size()) * i + 25;
		(*it)->getTarget()->setPosition(epi::Vector2f(posx, posy));
	}

	//send message to network
	this->_broadcastPacket(PacketFactory::createPacketStartGame(), true);

	for (auto it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		this->addGameObject((*it)->getTarget());
	}

	this->_clock.reset();
}

void		Game::removeGameObject(GameObject* toberemoved, GameObject* by)
{
	LockGuard		g1(this->_m_toBeDeleted);


	toberemoved->destroy();

	this->_toBeDeleted.push_back(toberemoved);

	/*debug*/
	Logger::logInfo("in room " + this->_room->getName() + " deleted gameobject " + epi::toString<int>(toberemoved->getId()));

	//send message to network
	this->_broadcastPacket(PacketFactory::createPacketDestroyEntity(toberemoved->getId()), true);
}

void		Game::addGameObject(GameObject* tobeadded)
{
	LockGuard		g1(this->_m_toBeAdded);

	tobeadded->setId(this->_generateId());
	tobeadded->setGame(this);
	tobeadded->initialize();

	//send message to network
	this->_broadcastPacket(PacketFactory::createPacketSpawnEntity(tobeadded->getId(), tobeadded->getTypeid(), tobeadded->getPosition().x, tobeadded->getPosition().y), true);

	this->_toBeAdded.push_back(tobeadded);

	/*debug*/
	Logger::logInfo("in room " + this->_room->getName() + " added gameobject " + epi::toString<int>(tobeadded->getId()));

}

void		Game::addClient(Connexion* c)
{
	GameObject*	go = GameObjectFactory::getInstance()->createGameObject("player");

	ClientBehaviour*	bh = go->getAttachedBehaviour<ClientBehaviour>();

	bh->setConnexion(c);
	go->setTag(go->getTag() + "_" + c->getLogin());
	Logger::logInfo("client tag : " + go->getTag());

	this->_clients.push_back(bh);
}

GameObject*	Game::findGameObjectByTag(const std::string& tag) const
{
	LockGuard		g1(this->_m_entities);

	for (auto it = this->_entities.begin(); it != this->_entities.end(); ++it)
	{
		if ((*it)->getTag() == tag)
		{
			return (*it);
		}
	}
	return 0;
}


void		Game::update()
{
	//udapting map
	/*OLOLE ULTRA TMP*/
	//this->_map->update();

	//delete entities to be deleted
	{
		LockGuard		g1(this->_m_toBeDeleted);

		for (auto it = this->_toBeDeleted.begin(); it != this->_toBeDeleted.end(); ++it)
		{
			delete (*it);
			{
				LockGuard		g1(this->_m_entities);
				this->_entities.remove((*it));
			}
		}
		this->_toBeDeleted.clear();
	}

	//add entities to be added
	{
		LockGuard		g1(this->_m_toBeAdded);

		for (auto it = this->_toBeAdded.begin(); it != this->_toBeAdded.end(); ++it)
		{
			{
				LockGuard		g1(this->_m_entities);
				this->_entities.push_back((*it));
			}
		}
		this->_toBeAdded.clear();
	}

	//update all entities
	{
		LockGuard		g1(this->_m_entities);
		for (auto it = this->_entities.begin(); it != this->_entities.end(); ++it)
		{
			(*it)->update();
		}
	}
}

void		Game::_broadcastPacket(PacketContainer* p, bool tcp)
{
	Singleton<NetworkManager>	*network = NULL;

	for (auto it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		network->getInstance()->sendPacket(p->getPacketSerialised(), (*it)->getConnexion(), tcp);
	}
}


int			Game::getSizeX() const
{
	return this->_sizex;
}

int			Game::getSizeY() const
{
	return this->_sizey;
}

void		Game::setMapSize(int x, int y)
{
	this->_sizex = x;
	this->_sizey = y;
}
