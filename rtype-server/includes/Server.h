/* Header de la classe du serveur. */
/* Auteur: Bertrand Boyer */
/* Commencé le 23/12/12. */
/* Dernière modification: 23/12/12. */

#ifndef __SERVER_H__
#define __SERVER_H__

#include <GlobalServerIncludes.h>

#include	<RoomManager.h>
#include	<NetworkManager.h>
#include	<Singleton.hpp>
#include	<ThreadPool.hh>
#include	<ActionManager.h>

class Server
{
public: //public methods

	Server();
	~Server();

	void	init();
	void	run();

private: //private attributes 
	Singleton<NetworkManager>	*_nManager;
	Singleton<RoomManager>		*_rManager;
	ThreadPool					*_tPool;
	ActionManager				*_aManager;
};


#endif /* __SERVER_H__ */
