#pragma once

#include	<map>
#include	<string>
#include	"GameObject.h"


class GameObjectFactory
{

public: //public types

	class IGameObjectCreationMethod
	{
	public: //public types
		
		virtual ~IGameObjectCreationMethod() {}

		virtual GameObject*		operator()() = 0;
	};

public: //public methods

	static GameObjectFactory*	getInstance();

	GameObject*		createGameObject(const std::string& name);
	void			addCreationMethod(const std::string& name, IGameObjectCreationMethod* meth);

private: //private methods

	GameObjectFactory();
	~GameObjectFactory();

	static GameObject*		createPlayer();
	static GameObject*		createBasicWall();

private: //private attributes

	static GameObjectFactory*	_instance;
	std::map<std::string, IGameObjectCreationMethod*>	_methods;
};