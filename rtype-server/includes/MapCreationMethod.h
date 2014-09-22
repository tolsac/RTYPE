#pragma once

#include	<string>
#include	<list>

#include	"ABehaviour.h"
#include	"GameObject.h"
#include	"GameObjectFactory.h"

class MapCreationMethod : public GameObjectFactory::IGameObjectCreationMethod
{
public: //public methods

	explicit MapCreationMethod(int ptypeid, int maxlife, const epi::Rect4f& boundingbox, const std::string& tag);
	~MapCreationMethod();

	void			addBehaviour(const std::string& name);

	GameObject*		operator()();

private: //private attributes

	int		_typeid;
	int		_maxLife;
	epi::Rect4f	_boundingBox;
	std::string _tag;
	std::list<std::string>	_bhs;
};
