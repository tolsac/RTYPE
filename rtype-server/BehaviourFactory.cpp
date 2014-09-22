#include	"BehaviourFactory.h"

#include	"ClientBehaviour.h"
#include	"WallBehaviour.h"
#include	"BulletBehaviour.h"


BehaviourFactory*	BehaviourFactory::_instance;

BehaviourFactory::BehaviourFactory()
{
	this->_methods["player"] = BehaviourFactory::createPlayer;
	this->_methods["wall"] = BehaviourFactory::createWall;
	this->_methods["bullet"] = BehaviourFactory::createBullet;
}

BehaviourFactory::~BehaviourFactory()
{

}

BehaviourFactory*	BehaviourFactory::getInstance()
{
	if (!BehaviourFactory::_instance)
	{
		BehaviourFactory::_instance = new BehaviourFactory();
		return BehaviourFactory::_instance;
	}
	else
	{
		return BehaviourFactory::_instance;
	}
}

ABehaviour*		BehaviourFactory::createBehaviour(const std::string& name)
{
	BehaviourFactory::behaviourCreationMethod meth = this->_methods[name];

	if (!meth)
	{
		return 0;
	}
	else
	{
		return meth();
	}
}

void			BehaviourFactory::addCreationMethod(const std::string& name, BehaviourFactory::behaviourCreationMethod meth)
{
	this->_methods[name] = meth;
}

ABehaviour*		BehaviourFactory::createPlayer()
{
	return new ClientBehaviour();
}

ABehaviour*		BehaviourFactory::createWall()
{
	return new WallBehaviour();
}

ABehaviour*		BehaviourFactory::createBullet()
{
	return new BulletBehaviour();
}
