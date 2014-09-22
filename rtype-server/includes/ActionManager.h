/* Header de la classe ActionManager*/
/* Auteur: Bertrand Boyer */
/* Commencé le 30/12/12. */
/* Dernière modification: 19/01/13. */

#ifndef __ACTIONMANAGER_H__
#define __ACTIONMANAGER_H__

#include <map>
#include <list>

#include <GlobalServerIncludes.h>
#include <PacketInfo.h>
#include <PacketFactory.h>
#include <ICallback.hh>
#include <Singleton.hpp>
#include <NetworkManager.h>
#include <RoomManager.h>

class ActionManager : public ICallback
{
private:
	typedef std::list<PacketInfo>	(ActionManager::*fctPtrClient_t)(PacketInfo*, bool&);
	std::map<int, fctPtrClient_t>	actionFromClient;

private:
	/* Fonctions traitants les paquets en provenance des clients. */
	std::list<PacketInfo>		clt_authentification(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_showRoom(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_createRoom(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_joinRoom(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_leaveRoom(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_launchGame(PacketInfo *pi, bool &sendToTCP);

	std::list<PacketInfo>		clt_movement(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_shooting(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_askDescribeEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_askPlayerScore(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		clt_askPlayerLife(PacketInfo *pi, bool &sendToTCP);

	/* Fonctions creant des paquets à destination des clients. */
	std::list<PacketInfo>		srv_authentificationOk(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_authentificationKo(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_roomDescription(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_createRoomOk(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_createRoomKo(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_joinRoomOk(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_joinRoomKo(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_leaveRoomOk(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_leaveRoomKo(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_launchGameOk(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_launchGameKo(PacketInfo *pi, bool &sendToTCP);

	std::list<PacketInfo>		srv_startGame(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_spawnEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_destroyEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_moveEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_lifeEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_collision(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_descriptionEntity(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_entityScore(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_playerDisconnect(PacketInfo *pi, bool &sendToTCP);
	std::list<PacketInfo>		srv_endGame(PacketInfo *pi, bool &sendToTCP);

public:
	ActionManager(void);
	~ActionManager(void);

	void		operator()();

	std::list<PacketInfo>		doAction(PacketInfo *pi, bool &sendToTCP);
};

#endif /* __ACTIONMANAGER_H__ */
