#pragma once

#include		"Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(int id, int idType, float PosX, float PosY, sf::Image *image);
	~Enemy();

	void getEnemy();

	virtual void updateAnim(float i);
};

