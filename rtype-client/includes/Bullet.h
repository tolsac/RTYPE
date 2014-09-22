#pragma once

#include		"Entity.h"

class Bullet : public Entity
{
	int		amplitude;
public:
	void getBullet();

	virtual void updateAnim(float i);
	Bullet(int id, int idType, float PosX, float PosY, sf::Image *image);
	~Bullet(void);
};
