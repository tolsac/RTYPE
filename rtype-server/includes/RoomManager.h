#ifndef		__ROOMMANAGER_HH__
#define		__ROOMMANAGER_HH__

#include	<string>
#include	<list>

#include	"ThreadPool.hh"
#include	"Room.h"
#include	"Mutex.hh"

class Connexion;

class RoomManager
{

public: //public types

	class RoomRunCallback : public ICallback
	{
	
	public: //public methods

		explicit RoomRunCallback(Room* room, RoomManager* manager);
		~RoomRunCallback();

		void	operator()();

	private: //private attributes

		Room*			_room;
		RoomManager*	_manager;
	};

public: //public methods

	RoomManager();
	~RoomManager();

	const std::list<Room*>&		getRoomList() const;
	Room*						createRoom(const std::string& roomName, Connexion* c, int difficulty, int idMap);
	Room*						getRoomByName(const std::string& roomName) const;
	Room*						getRoomByConnexion(Connexion* c) const;
	void						deleteRoomByName(const std::string& room);

private: //private attributes

	std::list<Room*>	_rooms;
	ThreadPool*			_threads;

private: //private mutexes

	mutable Mutex	_m_rooms;
};

#endif //__ROOMMANAGER_HH__
