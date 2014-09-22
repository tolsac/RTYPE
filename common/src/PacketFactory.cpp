/* Auteur: Bertrand Boyer */
/* Commencé le 23/12/12. */
/* Dernière modification: 23/12/12. */

#include <PacketFactory.h>
#include "Logger.h"

PacketFactory::PacketFactory(void)
{
}

PacketFactory::~PacketFactory(void)
{
}

#ifdef __CLIENT__

PacketContainer*			PacketFactory::createPacketAuthentification(char login[Protocol::SIZE_NAME])
{
	PacketContainer			*p = new PacketContainer(Protocol::AUTHENTIFICATION);

	p->addData(login, Protocol::SIZE_NAME);
	return (p);
}

PacketContainer*		PacketFactory::createPacketShowRoom(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::SHOW_ROOM);

	return (p);
}

PacketContainer*		PacketFactory::createPacketCreateRoom(const std::string& name, int maxPlayer, int difficulty, int idMap)
{
	PacketContainer		*p = new PacketContainer(Protocol::CREATE_ROOM);

	p->addData(name.substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);
	p->addData(&maxPlayer, sizeof(maxPlayer));
	p->addData(&difficulty, sizeof(difficulty));
	p->addData(&idMap, sizeof(idMap));
	return (p);
}

PacketContainer*		PacketFactory::createPacketJoinRoom(const std::string& name)
{
	PacketContainer		*p = new PacketContainer(Protocol::JOIN_ROOM);

	p->addData(name.substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);

	return (p);
}

PacketContainer*		PacketFactory::createPacketLeaveRoom(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::LEAVE_ROOM);

	return (p);
}

PacketContainer*		PacketFactory::createPacketLaunchGame(const std::string& name)
{
	PacketContainer		*p = new PacketContainer(Protocol::LAUNCH_GAME);

	p->addData(name.substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);
	return (p);
}

PacketContainer*		PacketFactory::createPacketMovement(int moveType)
{
	PacketContainer		*p = new PacketContainer(Protocol::MOVEMENT);

	p->addData(&moveType, sizeof(moveType));
	return (p);
}

PacketContainer*		PacketFactory::createPacketShooting(int idGun)
{
	PacketContainer		*p = new PacketContainer(Protocol::SHOOTING);

	p->addData(&idGun, sizeof(idGun));
	return (p);
}

PacketContainer*		PacketFactory::createPacketAskDescribeEntity(int idEntity)
{
	PacketContainer		*p = new PacketContainer(Protocol::ASK_DESCRIBE_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	return (p);
}

PacketContainer*		PacketFactory::createPacketAskPlayerScore(int idEntity)
{
	PacketContainer		*p = new PacketContainer(Protocol::ASK_PLAYER_SCORE);

	p->addData(&idEntity, sizeof(idEntity));
	return (p);
}

PacketContainer*		PacketFactory::createPacketAskPlayerLife(int idEntity)
{
	PacketContainer		*p = new PacketContainer(Protocol::ASK_PLAYER_LIFE);

	p->addData(&idEntity, sizeof(idEntity));
	return (p);
}

#elif defined __SERVER__

PacketContainer*		PacketFactory::createPacketAuthentificationOk(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::AUTHENTIFICATION_OK);

	return (p);
}

PacketContainer*		PacketFactory::createPacketAuthentificationKo(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::AUTHENTIFICATION_KO);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

PacketContainer*		PacketFactory::createPacketRoomDescription(const std::string& name, int maxPlayer, int currentPlayer, int difficulty, int idMap)
{
	PacketContainer		*p = new PacketContainer(Protocol::ROOM_DESCRIPTION);

	p->addData(name.substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);
	p->addData(&maxPlayer, sizeof(maxPlayer));
	p->addData(&currentPlayer, sizeof(currentPlayer));
	p->addData(&difficulty, sizeof(difficulty));
	p->addData(&idMap, sizeof(idMap));
	return (p);
}

PacketContainer*		PacketFactory::createPacketRoomPlayerList(std::string const& name, std::list<std::string> &lstPlayer)
{
	PacketContainer		*p = new PacketContainer(Protocol::ROOM_PLAYER_LIST);

	p->addData(name.substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);
	std::cout << "PacketFactory::createPacketRoomPlayerList -> size = " << lstPlayer.size() << std::endl;
	//Logger::logInfo("PacketFactory::createPacketRoomPlayerList -> size = " + epi::toString(lstPlayer.size()));
	for (auto it = lstPlayer.begin(); it != lstPlayer.end(); ++it)
	{
		p->addData((*it).substr(0, Protocol::SIZE_NAME).c_str(), Protocol::SIZE_NAME);
		Logger::logInfo("PacketFactory::createPacketRoomPlayerList -> string sent = " + (*it));
	}
	return (p);
}

PacketContainer*		PacketFactory::createPacketCreateRoomOk(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::CREATE_ROOM_OK);

	return (p);
}

PacketContainer*		PacketFactory::createPacketCreateRoomKo(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::CREATE_ROOM_KO);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

PacketContainer*		PacketFactory::createPacketJoinRoomOk(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::JOIN_ROOM_OK);

	return (p);
}

PacketContainer*		PacketFactory::createPacketJoinRoomKo(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::JOIN_ROOM_KO);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

PacketContainer*		PacketFactory::createPacketLeaveRoomOk(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::LEAVE_ROOM_OK);

	return (p);
}

PacketContainer*		PacketFactory::createPacketLeaveRoomKo(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::LAUNCH_GAME_KO);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

PacketContainer*		PacketFactory::createPacketLaunchGameOk(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::LAUNCH_GAME_OK);

	return (p);
}

PacketContainer*		PacketFactory::createPacketLaunchGameKo(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::LAUNCH_GAME_KO);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

PacketContainer*		PacketFactory::createPacketStartGame(void)
{
	PacketContainer		*p = new PacketContainer(Protocol::START_GAME);

	return (p);
}

PacketContainer*		PacketFactory::createPacketSpawnEntity(int idEntity, int idType, int posX, int posY)
{
	PacketContainer		*p = new PacketContainer(Protocol::SPAWN_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	p->addData(&idType, sizeof(idType));
	p->addData(&posX, sizeof(posX));
	p->addData(&posY, sizeof(posY));
	return (p);
}

PacketContainer*		PacketFactory::createPacketDestroyEntity(int idEntity)
{
	PacketContainer		*p = new PacketContainer(Protocol::DESTROY_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	return (p);
}

PacketContainer*		PacketFactory::createPacketMoveEntity(int idEntity, int posX, int posY, int moveType)
{
	PacketContainer		*p = new PacketContainer(Protocol::MOVE_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	p->addData(&posX, sizeof(posX));
	p->addData(&posY, sizeof(posY));
	p->addData(&moveType, sizeof(moveType));
	return (p);
}

PacketContainer*		PacketFactory::createPacketLifeEntity(int idEntity, int life)
{
	PacketContainer		*p = new PacketContainer(Protocol::LIFE_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	p->addData(&life, sizeof(life));
	return (p);
}

PacketContainer*		PacketFactory::createPacketCollision(int idEntity1, int idEntity2)
{
	PacketContainer		*p = new PacketContainer(Protocol::COLLISION);

	p->addData(&idEntity1, sizeof(idEntity1));
	p->addData(&idEntity2, sizeof(idEntity2));
	return (p);
}

PacketContainer*		PacketFactory::createPacketDescriptionEntity(int idEntity, int idType, int life, int posX, int posY)
{
	PacketContainer		*p = new PacketContainer(Protocol::DESCRIPTION_ENTITY);

	p->addData(&idEntity, sizeof(idEntity));
	p->addData(&idType, sizeof(idType));
	p->addData(&life, sizeof(life));
	p->addData(&posX, sizeof(posX));
	p->addData(&posY, sizeof(posY));
	return (p);
}

PacketContainer*		PacketFactory::createPacketEntityScore(int idEntity, int score)
{
	PacketContainer		*p = new PacketContainer(Protocol::ENTITY_SCORE);

	p->addData(&idEntity, sizeof(idEntity));
	p->addData(&score, sizeof(score));
	return (p);
}

PacketContainer*		PacketFactory::createPacketPlayerDisconnect(int idEntity)
{
	PacketContainer		*p = new PacketContainer(Protocol::PLAYER_DISCONNECT);

	p->addData(&idEntity, sizeof(idEntity));
	return (p);
}

PacketContainer*		PacketFactory::createPacketEndGame(int idMessage)
{
	PacketContainer		*p = new PacketContainer(Protocol::END_GAME);

	p->addData(&idMessage, sizeof(idMessage));
	return (p);
}

#endif
