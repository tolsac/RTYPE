#include "Player.h"

Player::Player()
{

}

Player::Player(int id, int idType, float PosX, float PosY, sf::Image *image) : Entity(id, idType, PosX, PosY, image)
{
	this->TimeElapsed = 0.0f;
	this->FrameSpeed = 0.2f;
	this->sizeSpriteMaxX = this->sprite.GetSize().x;
	this->sizeSpriteMaxY = this->sprite.GetSize().y;
	this->sizeSpriteX = this->sprite.GetSize().x / 5;
	this->sizeSpriteY = this->sprite.GetSize().y / 5;
	this->currentSpriteX = this->sizeSpriteX;
	this->currentSpriteY = this->sizeSpriteY;
	this->sprite.SetSubRect(sf::IntRect(0, 0, (int) this->currentSpriteX, (int) this->currentSpriteY));
}

Player::~Player()
{

}

void Player::updateAnim(float i)
{
	if (this->TimeElapsed >= this->FrameSpeed)
	{
		this->TimeElapsed = 0;
		if (this->currentSpriteX >= this->sizeSpriteMaxX)
			this->currentSpriteX = this->sizeSpriteX;
		else
			this->currentSpriteX += this->sizeSpriteX;
		this->sprite.SetSubRect(sf::IntRect((int) (this->currentSpriteX - this->sizeSpriteX), (int) (this->currentSpriteY - this->sizeSpriteY), (int) this->currentSpriteX, (int) this->currentSpriteY));
	}
	else
	this->TimeElapsed += i;

}

//TODO: REMOVE THIS METHOD BEFORE RELEASE
void Player::getPlayer()
{
	std::cout << "Je suis un player" << std::endl;
}
