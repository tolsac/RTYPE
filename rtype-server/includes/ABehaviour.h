#ifndef		__ABEHAVIOUR_H__
#define		__ABEHAVIOUR_H__

#include	"GameObject.h"

class Game;
class GameObject;

class ABehaviour
{
public: //public methods

	ABehaviour();
	virtual ~ABehaviour();

	virtual void		initialize() = 0;
	virtual void		update() = 0;
	virtual void		onCollision(GameObject* other) = 0;
	virtual void		onDestroy() = 0;
	virtual void		onMessage(GameObject* from, const std::string& message) = 0;

	void				setTarget(GameObject* target);
	GameObject*			getTarget() const;


protected:

	GameObject*		_gameobject;
};

#endif //__ABEHAVIOUR_H__
