#include	<fstream>
#include	<sstream>


#include	"Logger.h"
#include	"Convert.hh"
#include	"Game.h"
#include	"Rect.hpp"
#include	"Map.h"
#include	"Room.h"
#include	"MapCreationMethod.h"
#include	"GameObjectFactory.h"

Map::Map(Game* game)
	:	_game(game),
		_mapid(game->getRoom()->getIdMap())
{
	this->_methods["load_mob_type"] = &Map::_parse_load_mob_type;
	this->_methods["spawn_entity"] = &Map::_parse_spawn_entity;
	this->_methods["map_size"] = &Map::_parse_map_size;
}

Map::~Map()
{
}

/*
**	A TESTER REALLY
*/

void		Map::init()
{
	std::stringstream	ss;

	Logger::logInfo("initialazing map for room " + this->_game->getRoom()->getName());

	ss << "maps/map" << this->_mapid << ".txt";

	std::fstream	file;

	file.open(ss.str().c_str(), std::fstream::in);

	Logger::logInfo("file is open? : " + epi::toString<bool>(file.is_open()));

	std::string		line;
	while (std::getline(file, line))
	{
		std::stringstream	ss1(line);
		std::string		fword;

		ss1 >> fword;

		if (fword.length() > 0)
		{
			(this->*(this->_methods[fword]))(line);
		}
	}

	file.close();
}

void		Map::update()
{
	float	time = this->_game->getElapsedTime();

	bool	done = false;

	//Logger::logInfo("time = " + epi::toString(time));

	while (!done && !this->_spawns.empty())
	{
		float currtime = this->_spawns.front()->getTime();

		if (currtime < time)
		{
			MobSpawner*	spw = this->_spawns.front();
			this->_spawns.pop_front();

			GameObject*	go = spw->spawn();
			this->_game->addGameObject(go);
		}
		else
		{
			done = true;
		}
	}
}

void		Map::_loadMobType(const std::string& ianame, const std::string& filename)
{
	std::fstream	file;
	std::string		line;

	int	ptypeid;
	int maxlife;
	epi::Rect4f	jbb;
	std::string	tag;

	file.open(filename.c_str(), std::fstream::in);

	std::getline(file, line);
	{
		std::stringstream	ss1(line);
		std::string		word;

		ss1 >> word >> ptypeid;
	}

	std::getline(file, line);
	{
		std::stringstream	ss1(line);
		std::string		word;

		ss1 >> word >> maxlife;
	}

	std::getline(file, line);
	{
		std::stringstream	ss1(line);
		std::string		word;

		ss1 >> word >> jbb.x >> jbb.y >> jbb.width >> jbb.height;
	}

	std::getline(file, line);
	{
		std::stringstream	ss1(line);
		std::string		word;

		ss1 >> word >> tag;
	}

	MapCreationMethod*	mcm = new MapCreationMethod(ptypeid, maxlife, jbb, tag);

	while (std::getline(file, line))
	{
		std::stringstream	ss1(line);
		std::string		fword, sword;

		ss1 >> fword >> sword;
		mcm->addBehaviour(sword);
	}

	file.close();

	GameObjectFactory::getInstance()->addCreationMethod(ianame, mcm);
}

void		Map::_parse_load_mob_type(const std::string& line)
{
	std::stringstream	ss1(line);
	std::string		fword, sword, tword;


	Logger::logInfo("loading mob type ! -> line = " + line);
	ss1 >> fword >> sword >> tword;
	this->_loadMobType(sword, tword);
}

void		Map::_parse_spawn_entity(const std::string& line)
{
	std::stringstream	ss1(line);
	float			time;
	std::string		fword, ianame;
	epi::Vector2f	pos;


	Logger::logInfo("parsing mob spawn ! -> line = " + line);

	ss1 >> fword >> time >> ianame >> pos.x >> pos.y;

	Logger::logInfo("parsing mob spawn  -> time = " + epi::toString(time) + " ianame = " + ianame + " pos.x = " + epi::toString(pos.x) + " pos.y = " + epi::toString(pos.y));

	MobSpawner*		mobspw = new MobSpawner(time, ianame, pos);
	this->_spawns.push_back(mobspw);
}

void		Map::_parse_map_size(const std::string& line)
{
	std::stringstream	ss1(line);
	std::string			fword;
	int		x;
	int		y;

	ss1 >> fword >> x >> y;
	this->_game->setMapSize(x, y);
}
