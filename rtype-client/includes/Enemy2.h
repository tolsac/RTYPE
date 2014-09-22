#pragma once

#include	"Entity.h"

class Enemy2 : public Entity
{
	int		amplitude;
public:
	Enemy2();
	Enemy2(int id, int idType, float PosX, float PosY, sf::Image *image);
	~Enemy2();

	void getEnemy2();

	virtual void updateAnim(float i);
};