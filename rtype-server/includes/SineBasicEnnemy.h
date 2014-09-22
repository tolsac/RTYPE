#pragma once

#include	"ABehaviour.h"
#include	"Game.h"
#include	<cstdlib>

class Game;
class GameObject;

class SineBasicEnnemy : public ABehaviour
{

public: //public methods

	SineBasicEnnemy();
	~SineBasicEnnemy();

	void		initialize();
	void		update();
	void		onCollision(GameObject* other);
	void		onDestroy();
	void		onMessage(GameObject* from, const std::string& message);

private: //private attributes

	int			_amplitude;
};