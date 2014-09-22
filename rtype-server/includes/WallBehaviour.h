#ifndef		__WALLBEHAVIOUR_H__
#define		__WALLBEHAVIOUR_H__

#include	"ABehaviour.h"

class	WallBehaviour : public ABehaviour
{
public: //public methods

	WallBehaviour();
	~WallBehaviour();

	void		initialize();
	void		update();
	void		onCollision(GameObject* other);
	void		onDestroy();
	void		onMessage(GameObject* from, const std::string& message);

};

#endif		//__WALLBEHAVIOUR_H__
