#include	"MobSpawner.h"
#include	"GameObjectFactory.h"

MobSpawner::MobSpawner(float time, const std::string& ianame, const epi::Vector2f& pos)
	:	_time(time),
		_ianame(ianame),
		_position(pos)
{
}

MobSpawner::~MobSpawner()
{
}

float				MobSpawner::getTime() const
{
	return this->_time;
}

const std::string&	MobSpawner::getIaName() const
{
	return this->_ianame;
}

const epi::Vector2f&	MobSpawner::getPosition() const
{
	return this->_position;
}

GameObject*			MobSpawner::spawn()
{
	GameObject* go = GameObjectFactory::getInstance()->createGameObject(this->_ianame);

	go->setPosition(this->_position);
	return go;
}
