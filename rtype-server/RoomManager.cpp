#include	"RoomManager.h"
#include	"LockGuard.h"
#include	"Logger.h"

RoomManager::RoomManager()
{
	this->_threads = new ThreadPool();
}

RoomManager::~RoomManager()
{
	Logger::logInfo("destroying roommanager");
	this->_threads->joinAll();
	delete this->_threads;
}

Room*	RoomManager::createRoom(const std::string& roomName, Connexion* c, int difficulty, int idMap)
{
	LockGuard	g1(this->_m_rooms);

	Room*	room = new Room(roomName, c, this, difficulty, idMap);

	this->_rooms.push_back(room);
	ICallback*	call = new RoomManager::RoomRunCallback(room, this);

	this->_threads->runTask(call);
	return room;
}

Room*	RoomManager::getRoomByName(const std::string& roomName) const
{
	LockGuard	g1(this->_m_rooms);

	for (auto it = this->_rooms.begin(); it != this->_rooms.end(); ++it)
	{
		if ((*it)->getName() == roomName)
		{
			return (*it);
		}
	}
	return (NULL);
}


Room*	RoomManager::getRoomByConnexion(Connexion* c) const
{
	for (auto it = this->_rooms.begin(); it != this->_rooms.end(); ++it)
	{
		if ((*it)->containsClient(c))
		{
			return (*it);
		}
	}
	return 0;
}

void	RoomManager::deleteRoomByName(const std::string& roomName)
{
	LockGuard	g1(this->_m_rooms);

	Logger::logInfo("deleting room " + roomName);

	for (auto it = this->_rooms.begin(); it != this->_rooms.end(); ++it)
	{
		if ((*it)->getName() == roomName)
		{
			delete (*it);
			this->_rooms.erase(it);
			return;
		}
	}
}

const std::list<Room*>&	RoomManager::getRoomList() const
{
	return this->_rooms;
}


RoomManager::RoomRunCallback::RoomRunCallback(Room *room, RoomManager* manager)
	:	_room(room),
		_manager(manager)
{
}

RoomManager::RoomRunCallback::~RoomRunCallback()
{
}


void		RoomManager::RoomRunCallback::operator()()
{
	this->_room->run();
	this->_manager->deleteRoomByName(this->_room->getName());
}
