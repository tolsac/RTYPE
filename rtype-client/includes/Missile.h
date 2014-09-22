#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "Entity.h"

class Missile : public Entity
{
public:
	Missile();
	Missile(int id, int idType, float PosX, float PosY, sf::Image *image);
	~Missile();

	void getMissile();

	virtual void updateAnim(float i);
private:

};

#endif /*__MISSILE_H__*/