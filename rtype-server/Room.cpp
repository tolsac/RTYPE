#include	<Room.h>
#include "Connexion.h"

Room::Room(const std::string& roomName, Connexion* c, RoomManager* manager, int difficulty, int idMap)
	:	_name(roomName),
		_state(Room::CREATING),
		_nbPlayers(0),
		_maxNbPlayers(Protocol::DEFAULT_MAX_PLAYER_NUMBER),
		_game(0),
		_manager(manager),
		_running(false),
		_difficulty(difficulty),
		_idMap(idMap)
{
	this->addClient(c);
	Logger::logInfo("created room : " + roomName);
}

Room::~Room()
{
	if (this->_game)
	{
		delete this->_game;
	}
}

bool				Room::addClient(Connexion* c)
{
	if (this->_nbPlayers == this->_maxNbPlayers)
	{
		return false;
	}

	//doing amazing stuffe

	this->_connexions.push_back(c);
	this->_nbPlayers++;

	Logger::logInfo("added client to room " + this->_name);

	return true;
}

bool		Room::removeClient(Connexion* c)
{

	if (this->_nbPlayers == 0)
	{
		return false;
	}

	auto todel = std::find(this->_connexions.begin(), this->_connexions.end(), c);

	if (todel == this->_connexions.end())
	{
		return false;
	}

	this->_connexions.erase(todel);
	this->_nbPlayers--;

	if (this->_nbPlayers == 0)
	{
		this->stop();
	}

	return true;
}


void		Room::launchGame()
{
	LockGuard	g1(this->_m_game);

	Logger::logInfo("lauching game " + this->_name);

	if (this->_game)
	{
		return;
	}
	this->_game = new Game(this);

	Logger::logInfo("lauched game " + this->_name);

	for (auto it = this->_connexions.begin(); it != this->_connexions.end(); ++it)
	{
		this->_game->addClient((*it));
	}

	Logger::logInfo("lauched game " + this->_name);

	this->_game->init();
}

void				Room::setMaxPlayerNumber(int maxPlayer)
{
	this->_maxNbPlayers = maxPlayer;
}

Room::eRoomState	Room::getState() const
{
	return this->_state;
}

const std::string&	Room::getName() const
{
	return this->_name;
}

int					Room::getPlayersCount() const
{
	return this->_nbPlayers;	
}

int					Room::getMaxPlayerNumber() const
{
	return this->_maxNbPlayers;
}

const Clock&		Room::getClock() const
{
	return this->_clock;
}

Game*							Room::getGame() const
{
	return this->_game;
}


int					Room::getDifficulty() const
{
	return (this->_difficulty);
}

int					Room::getIdMap() const
{
	return (this->_idMap);
}

const std::list<Connexion*>		Room::getPlayersInRoom() const
{
	return (this->_connexions);
}

bool				Room::containsClient(Connexion* c) const
{
	for (auto it = this->_connexions.begin(); it != this->_connexions.end(); ++it)
	{
		if ((*it)->getIp() == c->getIp())
		{
			return true;
		}
	}
	return false;
}

Connexion*			Room::getConnexionByIpAddr(Connexion* c) const
{
	for (auto it = this->_connexions.begin(); it != this->_connexions.end(); ++it)
	{
		if ((*it)->getIp() == c->getIp())
		{
			return (*it);
		}
	}
	return 0;
}

void				Room::update()
{
	//Logger::logInfo("tmp : udapting room " + this->_name);

	if (this->_game)
	{
		LockGuard	g1(this->_m_game);
		this->_game->update();
	}
	else
	{
		
	}
}

void				Room::_synchronise()
{
	float	desiredTime = 1.0f / 60.0f;
	float	time = this->_clock.getElapsedTime();

	if (time < desiredTime)
	{
		this->_clock.sleep(desiredTime - time);
	}
	this->_clock.reset();
}

void				Room::stop()
{

	{
		LockGuard	g1(this->_m_isRunning);
		this->_running = false;
	}
	Logger::logInfo("room " + this->_name + " stopped");
}

void				Room::run()
{
	bool			runornot = true;
	{
		LockGuard	g1(this->_m_isRunning);
		this->_running = true;
	}
	Logger::logInfo("room " + this->_name + " launched");
	while (runornot)
	{
		this->update();
		{
			LockGuard	g1(this->_m_isRunning);

			runornot = this->_running;
		}
		this->_synchronise();
	}
}
