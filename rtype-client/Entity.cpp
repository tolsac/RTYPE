#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(int id, int idType, float PosX, float PosY, sf::Image *image)
{
	this->id = id;
	this->idType = idType;
	this->posX = PosX;
	this->posY = PosY;
	this->sprite.SetImage(*image);
}

Entity::~Entity()
{

}

float	Entity::getPosX()
{
	return (this->posX);
}

float	Entity::getPosY()
{
	return (this->posY);
}

float		Entity::getDestX()
{
	return (this->DestX);
}

float		Entity::getDestY()
{
	return (this->DestY);
}

int		Entity::getId()
{
	return (this->id);
}

int		Entity::getIdType()
{
	return (this->idType);
}

sf::Sprite Entity::getSprite()
{
	return (this->sprite);
}

void	Entity::setImageSprite(sf::Image &image)
{
	this->sprite.SetImage(image);
}

void	Entity::setPosSprite(float posX, float posY)
{
	this->sprite.SetPosition(posX, posY);
}

void	Entity::setPosX(float posX)
{
	this->posX = posX;
}

void	Entity::setPosY(float posY)
{
	this->posY = posY;
}

void		Entity::setDestSprite(float posX, float posY)
{
	this->setDestX(posX);
	this->setDestX(posY);
}

void		Entity::setDestX(float posX)
{
	this->DestX = posX;
}

void		Entity::setDestY(float posY)
{
	this->DestY = posY;
}

void		Entity::updatePosition(float i)
{
	if (this->TimeElapsed >= this->FrameSpeed)
	{
		this->TimeElapsed = 0;
		if ((this->DestX - this->posX) > 0)
			this->posX++;
		else if ((this->DestX - this->posX) < 0)
			this->posX--;
		if ((this->DestY - this->posY) > 0)
			this->posY++;
		else if ((this->DestY - this->posY) < 0)
			this->posY--;
	}
	else
	this->TimeElapsed += i;
	this->setPosSprite(this->posX, this->posY);
}