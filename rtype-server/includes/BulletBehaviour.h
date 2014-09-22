#pragma once

#include		"ABehaviour.h"
#include		"Game.h"

class			BulletBehaviour : public ABehaviour
{

public: //public methods
	void		initialize();
	void		update();
	void		onCollision(GameObject* other);
	void		onDestroy();
	void		onMessage(GameObject* from, const std::string& message);

	BulletBehaviour(void);
	~BulletBehaviour(void);

private: //private attributes

	int			_lives;
};

