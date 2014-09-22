#include	"MapCreationMethod.h"

#include	"BehaviourFactory.h"

MapCreationMethod::MapCreationMethod(int ptypeid, int maxlife, const epi::Rect4f& boundingbox, const std::string& tag)
	:	_typeid(ptypeid),
		_maxLife(maxlife),
		_boundingBox(boundingbox),
		_tag(tag)
{
}

MapCreationMethod::~MapCreationMethod()
{
}

void			MapCreationMethod::addBehaviour(const std::string& name)
{
	this->_bhs.push_back(name);
}

GameObject*		MapCreationMethod::operator()()
{
	GameObject*	gameobject = new GameObject();

	gameobject->setTypeId(this->_typeid);
	gameobject->setRemainingLife(this->_maxLife);
	gameobject->setMaximumLife(this->_maxLife);
	gameobject->setBoundingBox(this->_boundingBox);
	gameobject->setTag(this->_tag);

	for (auto it = this->_bhs.begin(); it != this->_bhs.end(); ++it)
	{
		gameobject->attachBehaviour(BehaviourFactory::getInstance()->createBehaviour((*it)));
	}

	return gameobject;
}