#ifndef		__ROOM_H__
#define		__ROOM_H__


#include	<string>
#include	<algorithm>

#include	<Protocol.h>
#include	"Clock.h"
#include	"Mutex.hh"
#include	"Game.h"
#include	"RoomManager.h"
#include	"LockGuard.h"
#include	"Logger.h"

class RoomManager;
class Connexion;

class Room
{
public: //public types

	enum eRoomState
	{
		CREATING,
		RUNNING
	};

private: //private attributes
	std::string				_name;
	eRoomState				_state;
	int						_nbPlayers;
	int						_maxNbPlayers;
	Game*					_game;
	RoomManager*			_manager;
	bool					_running;
	int						_difficulty;
	int						_idMap;
	std::list<Connexion*>	_connexions;
	Clock					_clock;

private: //private mutexes

	mutable Mutex			_m_isRunning;
	mutable Mutex			_m_game;

public: //public methods
	explicit Room(const std::string& roomName, Connexion* c, RoomManager* manager, int difficulty, int idMap);
	~Room();

	void							launchGame();
	void							run();
	void							update();
	void							stop();

	void							kick(const std::string& login);
	bool							addClient(Connexion* c);
	bool							removeClient(Connexion* c);
	bool							containsClient(Connexion* c) const;
	Connexion*						getConnexionByIpAddr(Connexion* c) const;

	void							setMaxPlayerNumber(int maxPlayer);

	eRoomState						getState() const;
	const std::string&				getName() const;
	int								getPlayersCount() const;
	int								getMaxPlayerNumber() const;
	const Clock&					getClock() const;
	int								getDifficulty() const;
	int								getIdMap() const;
	const std::list<Connexion*>		getPlayersInRoom() const;
	Game*							getGame() const;

private: //private methods
	void							_synchronise();
};

#endif //__ROOM_H__
