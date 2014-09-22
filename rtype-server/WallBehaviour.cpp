#include	"WallBehaviour.h"
#include	"Game.h"

WallBehaviour::WallBehaviour()
{
}

WallBehaviour::~WallBehaviour()
{

}

void		WallBehaviour::initialize()
{

}

void		WallBehaviour::update()
{
}

void		WallBehaviour::onCollision(GameObject* other)
{
	other->setRemainingLife(other->getRemainingLife() - 1);
	if (other->getRemainingLife() == 0)
	{
		this->getTarget()->getGame()->removeGameObject(other, this->getTarget());
	}
}

void		WallBehaviour::onDestroy()
{
}

void		WallBehaviour::onMessage(GameObject* from, const std::string& message)
{
}
