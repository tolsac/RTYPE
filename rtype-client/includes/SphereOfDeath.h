#pragma once

#include		"Entity.h"

class SphereOfDeath : public Entity
{
	int		amplitude;
public:
	void getBullet();

	virtual void updateAnim(float i);
	SphereOfDeath(int id, int idType, float PosX, float PosY, sf::Image *image);
	~SphereOfDeath(void);
};
