#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	Entity(int id, int idType, float PosX, float PosY, sf::Image *image);
	virtual ~Entity();
	virtual float		getPosX();
	virtual float		getPosY();
	virtual float		getDestX();
	virtual float		getDestY();
	virtual int			getId();
	virtual int			getIdType();
	virtual sf::Sprite	getSprite();
	virtual void		setImageSprite(sf::Image &image);
	virtual void		setPosSprite(float posX, float posY);
	virtual void		setPosX(float posX);
	virtual void		setPosY(float posY);
	
	virtual void		setDestSprite(float posX, float posY);
	virtual void		setDestX(float posX);
	virtual void		setDestY(float posY);

	virtual void		updateAnim(float i) {};
	virtual void		updatePosition(float i);
protected:
	int			id;
	int			idType;
	float		posX;
	float		posY;
	float		DestX;
	float		DestY;
	float		sizeSpriteX;
	float		sizeSpriteY;
	float		currentSpriteX;
	float		currentSpriteY;
	float		sizeSpriteMaxX;
	float		sizeSpriteMaxY;
	float		FrameSpeed;
	float		TimeElapsed;
	sf::Sprite sprite;
};

#endif /*__ENTITY_H__*/