#pragma once

#include	<string>
#include	<map>

#include	"Game.h"
#include	"MobSpawner.h"

class Game;
class GameObject;

class Map
{

public: //public methods

	explicit Map(Game* game);
	~Map();

	void		init();
	void		update();

private: //private types

	typedef	void		(Map::*t_parse_method)(const std::string&);

private: //private methods

	void		_loadMobType(const std::string& ianame, const std::string& filename);

	void		_parse_load_mob_type(const std::string& line);
	void		_parse_spawn_entity(const std::string& line);
	void		_parse_map_size(const std::string& line);

private: //private attributes

	Game*	_game;
	int		_mapid;
	std::map<std::string, t_parse_method>	_methods;
	std::list<MobSpawner*>	_spawns;
};
