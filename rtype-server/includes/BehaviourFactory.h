#pragma once

#include	<map>
#include	<string>

#include	"ABehaviour.h"

class BehaviourFactory
{

public: //public types

	typedef	ABehaviour*	(*behaviourCreationMethod)();

public: //public methods

	static BehaviourFactory*	getInstance();


	ABehaviour*		createBehaviour(const std::string& name);
	void			addCreationMethod(const std::string& name, behaviourCreationMethod meth);

private: //private methods

	BehaviourFactory();
	~BehaviourFactory();

	static ABehaviour*		createPlayer();
	static ABehaviour*		createWall();
	static ABehaviour*		createBullet();

private: //private attributes

	static BehaviourFactory*	_instance;
	std::map<std::string, behaviourCreationMethod>	_methods;
};
