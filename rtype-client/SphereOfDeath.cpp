#include "SphereOfDeath.h"

SphereOfDeath::SphereOfDeath(int id, int idType, float PosX, float PosY, sf::Image *image) : Entity(id, idType, PosX, PosY, image)
{
	this->TimeElapsed = 0.0f;
	this->FrameSpeed = 0.2f;
	this->sizeSpriteMaxX = this->sprite.GetSize().x;
	this->sizeSpriteMaxY = this->sprite.GetSize().y;
	this->sizeSpriteX = this->sprite.GetSize().x / 12;
	this->sizeSpriteY = this->sprite.GetSize().y;
	this->currentSpriteX = this->sizeSpriteX;
	this->currentSpriteY = this->sizeSpriteY;
	this->sprite.SetSubRect(sf::IntRect(0, 0, this->currentSpriteX, this->currentSpriteY));
}

SphereOfDeath::~SphereOfDeath()
{

}

void SphereOfDeath::updateAnim(float i)
{
	if (this->TimeElapsed >= this->FrameSpeed)
	{
		this->TimeElapsed = 0;
		//std::cout << "updatesprite : " << i << std::endl;
		if (this->currentSpriteX >= this->sizeSpriteMaxX)
			this->currentSpriteX = this->sizeSpriteX;
		else
			this->currentSpriteX += this->sizeSpriteX;
		this->sprite.SetSubRect(sf::IntRect(this->currentSpriteX - this->sizeSpriteX, this->currentSpriteY - this->sizeSpriteY, this->currentSpriteX, this->currentSpriteY));
	}
	else
	this->TimeElapsed += i;
}