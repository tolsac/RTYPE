#ifndef		__FIREINGENNEMY_H__
#define		__FIREINGENNEMY_H__

#include	"Clock.h"
#include	"ABehaviour.h"

class FireingEnnemy : public ABehaviour
{

public: //public methods

	FireingEnnemy();
	~FireingEnnemy();

	void		initialize();
	void		update();
	void		onCollision(GameObject* other);
	void		onDestroy();
	void		onMessage(GameObject* from, const std::string& message);

	void		setTimeToFire(float time);

private: //private attributes

	Clock	_clock;
	float	_timeToFire;
	bool	_fireing;

};

#endif //__FIREINGENNEMY_H__
