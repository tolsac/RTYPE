#include	"ClientBehaviour.h"

#include	<sstream>
#include	"Logger.h"
#include	"Protocol.h"
#include	"Convert.hh"
#include	"GameObjectFactory.h"
#include	"Game.h"


ClientBehaviour::ClientBehaviour()
	:	_connexion(0),
		_fireing(false)
{

}

ClientBehaviour::~ClientBehaviour()
{
}

void		ClientBehaviour::initialize()
{
}

void		ClientBehaviour::update()
{
}

void		ClientBehaviour::onCollision(GameObject* other)
{

}

void		ClientBehaviour::onDestroy()
{

}

void		ClientBehaviour::onMessage(GameObject* from, const std::string& message)
{
	std::stringstream	ss(message);
	std::string			fword;
	int					sword;

	ss >> fword >> sword;
	if (fword == "move")
	{
		if (sword == Protocol::MOVE_UP)
		{
			this->getTarget()->move(epi::Vector2f(0.0f, -20.0f));		
		}
		else if (sword == Protocol::MOVE_DOWN)
		{
			this->getTarget()->move(epi::Vector2f(0.0f, 20.0f));		
		}
		else if (sword == Protocol::MOVE_LEFT)
		{
			this->getTarget()->move(epi::Vector2f(-20.0f, 0));
		}
		else if (sword == Protocol::MOVE_RIGHT)
		{
			this->getTarget()->move(epi::Vector2f(20.0f, 0));
		}
	}
	else if (fword == "fire")
	{
		if (this->_fireing == true)
		{
			if (this->_clock.getElapsedTime() > 0.5f)
			{
				this->_fireing = false;
			}
		}
		else
		{
			GameObject*		bullet = GameObjectFactory::getInstance()->createGameObject("bullet");
			bullet->setParent(this->getTarget());
			bullet->setPosition(epi::Vector2f(this->getTarget()->getPosition().x + this->getTarget()->getBoundingBox().x - bullet->getBoundingBox().width / 2 + 10,
				this->getTarget()->getPosition().y));
			this->getTarget()->getGame()->addGameObject(bullet);
			this->_fireing = true;
			this->_clock.reset();
		}
	}
}

void		ClientBehaviour::setConnexion(Connexion* c)
{
	this->_connexion = c;
}

Connexion*	ClientBehaviour::getConnexion() const
{
	return this->_connexion;
}
