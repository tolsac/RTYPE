#include	"FireingEnnemy.h"
#include	"Logger.h"
#include	"GameObjectFactory.h"
#include	"Game.h"

FireingEnnemy::FireingEnnemy()
	:	_timeToFire(1.0f),
		_fireing(false)
{
}

FireingEnnemy::~FireingEnnemy()
{

}

void		FireingEnnemy::initialize()
{
	this->_clock.reset();
}

void		FireingEnnemy::update()
{
	if (this->_fireing)
	{
		if (this->_clock.getElapsedTime() > this->_timeToFire)
		{
			this->_fireing = false;
		}
	}
	else
	{
		Logger::logInfo("pew pew!");
		this->_fireing = true;
		GameObject*		bullet = GameObjectFactory::getInstance()->createGameObject("bullet");
		bullet->setParent(this->getTarget());
		bullet->setPosition(epi::Vector2f(this->getTarget()->getPosition().x + this->getTarget()->getBoundingBox().x - bullet->getBoundingBox().width / 2 - 10,
			this->getTarget()->getPosition().y));
		this->getTarget()->getGame()->addGameObject(bullet);
		//spawn une bouboule tqvu
	}
}

void		FireingEnnemy::onCollision(GameObject* other)
{

}

void		FireingEnnemy::onDestroy()
{
}

void		FireingEnnemy::onMessage(GameObject* from, const std::string& message)
{
}

void		FireingEnnemy::setTimeToFire(float time)
{
	this->_timeToFire = time;
}
