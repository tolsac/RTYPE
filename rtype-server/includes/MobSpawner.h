#ifndef		__MOBSPAWNER_H__
#define		__MOBSPAWNER_H__

#include	<string>

#include	"Vector.hpp"

#include	"GameObject.h"

class MobSpawner
{
public: //public methods

	explicit MobSpawner(float time, const std::string& ianame, const epi::Vector2f& pos);
	~MobSpawner();

	float				getTime() const;
	const std::string&	getIaName() const;
	const epi::Vector2f&	getPosition() const;

	GameObject*			spawn();

private: //private attributes

	float			_time;
	std::string		_ianame;
	epi::Vector2f	_position;
};

#endif //__MOBSPAWNER_H__
