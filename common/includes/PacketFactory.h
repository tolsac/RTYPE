/* Header de la classe PacketFactory. */
/* Auteur: Bertrand Boyer */
/* Commencé le 23/12/12. */
/* Dernière modification: 05/01/13. */

#ifndef __PACKETFACTORY_H__
#define __PACKETFACTORY_H__

#include <list>

#include <PacketContainer.h>

class PacketFactory
{
public:
	PacketFactory(void);
	~PacketFactory(void);

#ifdef __CLIENT__ /* Création des paquets pour la partie client. */
	static PacketContainer		*createPacketAuthentification(char login[Protocol::SIZE_NAME]);
	static PacketContainer		*createPacketShowRoom(void);
	static PacketContainer		*createPacketCreateRoom(const std::string& name, int maxPlayer, int difficulty, int idMap);
	static PacketContainer		*createPacketJoinRoom(const std::string& name);
	static PacketContainer		*createPacketLeaveRoom(void);
	static PacketContainer		*createPacketLaunchGame(const std::string& name);

	static PacketContainer		*createPacketMovement(int moveType);
	static PacketContainer		*createPacketShooting(int idGun);
	static PacketContainer		*createPacketAskDescribeEntity(int idEntity);
	static PacketContainer		*createPacketAskPlayerScore(int idEntity);
	static PacketContainer		*createPacketAskPlayerLife(int idEntity);

#elif defined __SERVER__ /* Création des paquets pour la partie serveur. */
	static PacketContainer		*createPacketAuthentificationOk(void);
	static PacketContainer		*createPacketAuthentificationKo(int idMessage);
	static PacketContainer		*createPacketRoomDescription(const std::string& name, int maxPlayer, int currentPlayer, int difficulty, int idMap);
	static PacketContainer		*createPacketRoomPlayerList(std::string const& name, std::list<std::string> &lstPlayer);
	static PacketContainer		*createPacketCreateRoomOk(void);
	static PacketContainer		*createPacketCreateRoomKo(int idMessage);
	static PacketContainer		*createPacketJoinRoomOk(void);
	static PacketContainer		*createPacketJoinRoomKo(int idMessage);
	static PacketContainer		*createPacketLeaveRoomOk(void);
	static PacketContainer		*createPacketLeaveRoomKo(int idMessage);
	static PacketContainer		*createPacketLaunchGameOk(void);
	static PacketContainer		*createPacketLaunchGameKo(int idMessage);

	static PacketContainer		*createPacketStartGame(void);
	static PacketContainer		*createPacketSpawnEntity(int idEntity, int idType, int posX, int posY);
	static PacketContainer		*createPacketDestroyEntity(int idEntity);
	static PacketContainer		*createPacketMoveEntity(int idEntity, int posX, int posY, int moveType);
	static PacketContainer		*createPacketLifeEntity(int idEntity, int life);
	static PacketContainer		*createPacketCollision(int idEntity1, int idEntity2);	// TODO: Not implemented yet.
	static PacketContainer		*createPacketDescriptionEntity(int idEntity, int idType, int life, int posX, int posY);
	static PacketContainer		*createPacketEntityScore(int idEntity, int score);
	static PacketContainer		*createPacketPlayerDisconnect(int idEntity);
	static PacketContainer		*createPacketEndGame(int idMessage);
#endif
};

#endif /* __PACKETFACTORY_H__ */
