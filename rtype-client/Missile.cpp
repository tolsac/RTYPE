#include "Missile.h"

Missile::Missile()
{

}

Missile::Missile(int id, int idType, float PosX, float PosY, sf::Image *image) : Entity(id, idType, PosX, PosY, image)
{
	this->sizeSpriteMaxX = this->sprite.GetSize().x;
	this->sizeSpriteMaxY = this->sprite.GetSize().y;
	this->currentSpriteX = this->sizeSpriteX;
	this->currentSpriteY = this->sizeSpriteY;
	this->sizeSpriteX = this->sprite.GetSize().x / 6.0f;
	this->sizeSpriteY = this->sprite.GetSize().y / 6.0f;
	this->sprite.SetSubRect(sf::IntRect(0, 0, (int) this->sizeSpriteX, (int) this->sizeSpriteY));
}

Missile::~Missile()
{

}

void Missile::updateAnim(float i)
{

}

//TODO: REMOVE THIS METHOD BEFORE RELEASE
void Missile::getMissile()
{
	std::cout << "Je suis un missile" << std::endl;
}

