#include	"ABehaviour.h"


ABehaviour::ABehaviour()
	:	_gameobject(0)
{
}

ABehaviour::~ABehaviour()
{
}

void				ABehaviour::setTarget(GameObject* target)
{
	this->_gameobject = target;
}

GameObject*			ABehaviour::getTarget() const
{
	return this->_gameobject;
}

