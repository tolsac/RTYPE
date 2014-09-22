#include "SineBasicEnnemy.h"

SineBasicEnnemy::SineBasicEnnemy()
{

}

SineBasicEnnemy::~SineBasicEnnemy()
{
}

void		SineBasicEnnemy::initialize()
{
	this->_amplitude = (int)(rand() % (this->getTarget()->getGame()->getSizeY() / 2)) + 100;
}

void		SineBasicEnnemy::update()
{
	this->_gameobject->move(epi::Vector2f(-(0.05f * this->getTarget()->getGame()->getElapsedTime()),
											this->_amplitude * std::sin(this->getTarget()->getGame()->getElapsedTime()) + (this->getTarget()->getGame()->getSizeY() / 2)));
}

void		SineBasicEnnemy::onCollision(GameObject* other)
{
}

void		SineBasicEnnemy::onDestroy()
{

}

void		SineBasicEnnemy::onMessage(GameObject* from, const std::string& message)
{

}
