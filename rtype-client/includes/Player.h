#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	Player(int id, int idType, float PosX, float PosY, sf::Image *image);
	~Player();

	void getPlayer();

	virtual void updateAnim(float i);
private:

};

#endif /*__PLAYER_H__*/