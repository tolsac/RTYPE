#ifndef		__CLIENTBEHAVIOUR_H__
#define		__CLIENTBEHAVIOUR_H__

#include	"ABehaviour.h"
#include	"Clock.h"

class Connexion;

class ClientBehaviour : public ABehaviour
{
public: //public methods

	ClientBehaviour();
	~ClientBehaviour();

	void		initialize();
	void		update();
	void		onCollision(GameObject* other);
	void		onDestroy();
	void		onMessage(GameObject* from, const std::string& message);

	void		setConnexion(Connexion* c);
	Connexion*	getConnexion() const;

private: //private attributes

	Connexion*	_connexion;
	Clock		_clock;
	bool		_fireing;
};

#endif //__CLIENTBEHAVIOUR_H__
