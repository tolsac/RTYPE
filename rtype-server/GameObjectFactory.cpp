#include	"GameObjectFactory.h"
#include	"BehaviourFactory.h"
#include	"MapCreationMethod.h"


GameObjectFactory*	GameObjectFactory::_instance;

GameObjectFactory::GameObjectFactory()
{
	MapCreationMethod*	mplayer = new MapCreationMethod(0, 3, epi::Rect4f(-10, -10, 20, 20), "player");
	mplayer->addBehaviour("player");

	MapCreationMethod*	mwall = new MapCreationMethod(1, -1, epi::Rect4f(-10, -30, 20, 60), "wall");
	mwall->addBehaviour("wall");

	MapCreationMethod*	mdwall = new MapCreationMethod(1, 2, epi::Rect4f(-10, -30, 20, 60), "wall");
	mdwall->addBehaviour("wall");

	MapCreationMethod*	mbullet = new MapCreationMethod(2, 1, epi::Rect4f(-5, -5, 10, 10), "bullet");
	mbullet->addBehaviour("bullet");

	this->addCreationMethod("player", mplayer);
	this->addCreationMethod("wall", mwall);
	this->addCreationMethod("destructible_wall", mdwall);
	this->addCreationMethod("bullet", mbullet);
}

GameObjectFactory::~GameObjectFactory()
{

}

GameObjectFactory*	GameObjectFactory::getInstance()
{
	if (!GameObjectFactory::_instance)
	{
		GameObjectFactory::_instance = new GameObjectFactory();
		return GameObjectFactory::_instance;
	}
	else
	{
		return GameObjectFactory::_instance;
	}
}

GameObject*		GameObjectFactory::createGameObject(const std::string& name)
{
	GameObjectFactory::IGameObjectCreationMethod* meth = this->_methods[name];

	if (!meth)
	{
		return 0;
	}
	else
	{
		return meth->operator()();
	}
}

void			GameObjectFactory::addCreationMethod(const std::string& name, GameObjectFactory::IGameObjectCreationMethod* meth)
{
	this->_methods[name] = meth;
}

GameObject*		GameObjectFactory::createPlayer()
{
	GameObject*	obj = new GameObject();


	ABehaviour*	bh = BehaviourFactory::getInstance()->createBehaviour("player");
	obj->attachBehaviour(bh);
	return obj;
}

GameObject*		GameObjectFactory::createBasicWall()
{
	return 0;
}
