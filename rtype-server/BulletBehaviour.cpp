#include "BulletBehaviour.h"
#include	"Room.h"


BulletBehaviour::BulletBehaviour()
{
	this->_lives = 100;
}


BulletBehaviour::~BulletBehaviour()
{
}

void		BulletBehaviour::initialize()
{
}

void		BulletBehaviour::update()
{
	//float	move = 500.0f * this->getTarget()->getGame()->getRoom()->getClock().getElapsedTime();

	this->getTarget()->move(epi::Vector2f(5.0f, 0));
	--this->_lives;
	if (this->_lives < 0)
	{
		this->getTarget()->getGame()->removeGameObject(this->getTarget(), 0);
	}
}

void		BulletBehaviour::onCollision(GameObject* other)
{
	/*
	other->setRemainingLife(other->getRemainingLife() - 1);
	if (other->getRemainingLife() == 0)
	{
		this->getTarget()->getGame()->removeGameObject(other, this->getTarget());
	}
	*/
}

void		BulletBehaviour::onDestroy()
{
}

void		BulletBehaviour::onMessage(GameObject* from, const std::string& message)
{
}
