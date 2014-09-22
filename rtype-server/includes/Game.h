#ifndef		__GAME_H__
#define		__GAME_H__

#include	<list>

#include	"Clock.h"
#include	"Mutex.hh"
#include	"Map.h"
#include	"GameObject.h"
#include	"ClientBehaviour.h"
#include	"PacketFactory.h"

class Room;
class Map;
class GameObject;
class Connexion;

class Game
{
public: //public methods

	explicit Game(Room* room);
	~Game();

	void		init();
	void		update();
	void		removeGameObject(GameObject* toberemoved, GameObject* by);
	void		addGameObject(GameObject* tobeadded);
	GameObject*	findGameObjectByTag(const std::string& tag) const;

	void		refreshEntity(GameObject* go, bool checkCollision = true);

	void		addClient(Connexion* c);

	Room*		getRoom() const;
	float		getElapsedTime() const;  //to rename
	int			getSizeX() const;
	int			getSizeY() const;

	void		setMapSize(int x, int y);

private: //private methods

	bool		_isColliding(GameObject* g1, GameObject* g2);
	void		checkCollision(GameObject* go);
	int			_generateId();
	void		_broadcastPacket(PacketContainer* p, bool tcp);

private: //private attributes

	std::list<GameObject*>	_entities;
	std::list<GameObject*>	_toBeDeleted;
	std::list<GameObject*>	_toBeAdded;
	std::list<ClientBehaviour*>	_clients;
	Map		*_map;
	int		_sizex;
	int		_sizey;
	Room*	_room;
	Clock	_clock;
	int		_currentId;

private: //private mutexes

	mutable Mutex	_m_toBeDeleted;
	mutable Mutex	_m_toBeAdded;
	mutable Mutex	_m_entities;

};

#endif	//__GAME_H__
