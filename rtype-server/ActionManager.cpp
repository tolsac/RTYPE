/* Auteur: Bertrand Boyer */
/* Commencé le 30/12/12. */
/* Dernière modification: 19/01/13. */

#include <ActionManager.h>
#include	"Convert.hh"

ActionManager::ActionManager(void)
{
	Logger::logInfo("Creation de la map des actions de l'ActionManager.");
	this->actionFromClient.insert(std::make_pair(Protocol::AUTHENTIFICATION, &ActionManager::clt_authentification));
	this->actionFromClient.insert(std::make_pair(Protocol::SHOW_ROOM, &ActionManager::clt_showRoom));
	this->actionFromClient.insert(std::make_pair(Protocol::CREATE_ROOM, &ActionManager::clt_createRoom));
	this->actionFromClient.insert(std::make_pair(Protocol::JOIN_ROOM, &ActionManager::clt_joinRoom));
	this->actionFromClient.insert(std::make_pair(Protocol::LEAVE_ROOM, &ActionManager::clt_leaveRoom));
	this->actionFromClient.insert(std::make_pair(Protocol::LAUNCH_GAME, &ActionManager::clt_launchGame));

	this->actionFromClient.insert(std::make_pair(Protocol::MOVEMENT, &ActionManager::clt_movement));
	this->actionFromClient.insert(std::make_pair(Protocol::SHOOTING, &ActionManager::clt_shooting));
	this->actionFromClient.insert(std::make_pair(Protocol::ASK_DESCRIBE_ENTITY, &ActionManager::clt_askDescribeEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::ASK_PLAYER_SCORE, &ActionManager::clt_askPlayerScore));
	this->actionFromClient.insert(std::make_pair(Protocol::ASK_PLAYER_LIFE, &ActionManager::clt_askPlayerLife));

	this->actionFromClient.insert(std::make_pair(Protocol::AUTHENTIFICATION_OK, &ActionManager::srv_authentificationOk));
	this->actionFromClient.insert(std::make_pair(Protocol::AUTHENTIFICATION_KO, &ActionManager::srv_authentificationKo));
	this->actionFromClient.insert(std::make_pair(Protocol::ROOM_DESCRIPTION, &ActionManager::srv_roomDescription));
	this->actionFromClient.insert(std::make_pair(Protocol::CREATE_ROOM_OK, &ActionManager::srv_createRoomOk));
	this->actionFromClient.insert(std::make_pair(Protocol::CREATE_ROOM_KO, &ActionManager::srv_createRoomKo));
	this->actionFromClient.insert(std::make_pair(Protocol::JOIN_ROOM_OK, &ActionManager::srv_joinRoomOk));
	this->actionFromClient.insert(std::make_pair(Protocol::JOIN_ROOM_KO, &ActionManager::srv_joinRoomKo));
	this->actionFromClient.insert(std::make_pair(Protocol::LEAVE_ROOM_OK, &ActionManager::srv_leaveRoomOk));
	this->actionFromClient.insert(std::make_pair(Protocol::LEAVE_ROOM_KO, &ActionManager::srv_leaveRoomKo));
	this->actionFromClient.insert(std::make_pair(Protocol::LAUNCH_GAME_OK, &ActionManager::srv_launchGameOk));
	this->actionFromClient.insert(std::make_pair(Protocol::LAUNCH_GAME_KO, &ActionManager::srv_launchGameKo));

	this->actionFromClient.insert(std::make_pair(Protocol::START_GAME, &ActionManager::srv_startGame));
	this->actionFromClient.insert(std::make_pair(Protocol::SPAWN_ENTITY, &ActionManager::srv_spawnEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::DESTROY_ENTITY, &ActionManager::srv_destroyEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::MOVE_ENTITY, &ActionManager::srv_moveEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::LIFE_ENTITY, &ActionManager::srv_lifeEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::COLLISION, &ActionManager::srv_collision));
	this->actionFromClient.insert(std::make_pair(Protocol::DESCRIPTION_ENTITY, &ActionManager::srv_descriptionEntity));
	this->actionFromClient.insert(std::make_pair(Protocol::ENTITY_SCORE, &ActionManager::srv_entityScore));
	this->actionFromClient.insert(std::make_pair(Protocol::PLAYER_DISCONNECT, &ActionManager::srv_playerDisconnect));
	this->actionFromClient.insert(std::make_pair(Protocol::END_GAME, &ActionManager::srv_endGame));
}

ActionManager::~ActionManager(void)
{
}

void							ActionManager::operator()()
{
	Singleton<NetworkManager>	*sNm = NULL;
	PacketInfo					*pi = NULL;
	std::list<PacketInfo>		answers;
	bool						sendToTCP = true;

	while (true)
	{
#ifdef PLATFORM_WIN32
		Sleep(100);
#endif
#ifdef PLATFORM_LINUX

#endif
		pi = sNm->getInstance()->readPacket();
		if (pi != NULL)
		{
			/* On fait les traitements sur le paquets. */
			answers = ActionManager::doAction(pi, sendToTCP);
			delete (pi->packet);
			delete (pi);
			/* On envoie les paquets de réponses. */
			for (auto it = answers.begin(); it != answers.end(); ++it)
			{
				/* Pour chaque paquet, on envoie sur la connexion. */
				sNm->getInstance()->sendPacket((*it).packet->getPacketSerialised(), (*it).connexion, sendToTCP);
				delete ((*it).packet);
			}
		}
	}
}

std::list<PacketInfo>			ActionManager::doAction(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answers;
	int							action;

	try
	{
		action = pi->packet->getCommandID();
		Logger::logInfo("Reception d'un paquet: " + Protocol::mapCommandName.at(action));
		answers = ((*this).*actionFromClient[action])(pi, sendToTCP);
		Logger::logInfo("Traitement du paquet termine.");
	}
	catch (const ServerException &se)
	{
		Logger::logError(se.what());
	}
	catch (const std::exception &e)
	{
		Logger::logError(e.what());
	}
	return (answers);
}

std::list<PacketInfo>			ActionManager::clt_authentification(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;
	PacketInfo					api;
	std::string					login;
	Singleton<NetworkManager>	*sNm = NULL;

	sendToTCP = true;
	if (sNm->getInstance()->takeConnexionList())
	{
		api.connexion = pi->connexion;
		Logger::logInfo("Liste des connexions prises.");
		login.assign(pi->packet->getData());
		if (sNm->getInstance()->getConnexionByLogin(login) == NULL)
		{
			Logger::logInfo("Creation du compte: " + login + ".");
			pi->connexion->setLogin(login);
			api.packet = PacketFactory::createPacketAuthentificationOk();
		}
		else
		{
			Logger::logInfo("Le compte \"" + login + " existe deja.");
			api.packet = PacketFactory::createPacketAuthentificationKo(Protocol::BAD_LOGIN);
		}
		sNm->getInstance()->releaseConnexionList();
		Logger::logInfo("Liste des connexions relachees.");
		answer.push_back(api);
	}
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_showRoom(PacketInfo *pi, bool &sendToTCP)
{
	PacketInfo					api;
	std::list<PacketInfo>		answer;
	Singleton<RoomManager>		*sRm = NULL;
	std::list<Room*>			lstRoom;
	Room						*r = NULL;

	sendToTCP = true;
	lstRoom = sRm->getInstance()->getRoomList();
	api.connexion = pi->connexion;
	for (auto it = lstRoom.begin(); it != lstRoom.end(); ++it)
	{
		r = *it;
		api.packet = NULL;
		api.packet = PacketFactory::createPacketRoomDescription(r->getName(), r->getMaxPlayerNumber(), r->getPlayersCount(), r->getDifficulty(), r->getIdMap());
		answer.push_back(api);
	}
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_createRoom(PacketInfo *pi, bool &sendToTCP)
{
	PacketInfo					api;
	std::list<PacketInfo>		answer;
	Singleton<RoomManager>		*sRm = NULL;
	std::string					roomName;
	char						roomNameSTR[Protocol::SIZE_NAME];
	int							maxPlayer;
	int							difficulty;
	int							idMap;
	int							offset = 0;

	sendToTCP = true;
	api.connexion = pi->connexion;
	pi->packet->extractData(offset, Protocol::SIZE_NAME, roomNameSTR);
	roomName.assign(roomNameSTR);
	offset = offset + Protocol::SIZE_NAME;
	pi->packet->extractData(offset, sizeof(maxPlayer), &maxPlayer);
	offset = offset + sizeof(maxPlayer);
	pi->packet->extractData(offset, sizeof(difficulty), &difficulty);
	offset = offset + sizeof(difficulty);
	pi->packet->extractData(offset, sizeof(idMap), &idMap);
	offset = offset + sizeof(idMap);
	if (sRm->getInstance()->getRoomByName(roomName) == NULL)
	{
		Logger::logInfo("Creation de la room \"" + roomName + "\".");
		sRm->getInstance()->createRoom(roomName, pi->connexion, difficulty, idMap);
		api.packet = PacketFactory::createPacketCreateRoomOk();
	}
	else
	{
		Logger::logInfo("La room \"" + roomName + "\" existe deja.");
		api.packet = PacketFactory::createPacketCreateRoomKo(Protocol::ROOM_ALREADY_EXISTS);
	}
	answer.push_back(api);
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_joinRoom(PacketInfo *pi, bool &sendToTCP)
{
	PacketInfo					api;
	std::list<PacketInfo>		answer;
	Singleton<RoomManager>		*sRm = NULL;
	Room						*roomToJoin = NULL;
	std::string					roomName;
	char						roomNameSTR[Protocol::SIZE_NAME];
	std::list<Connexion*>		players;
	std::list<std::string>		playersName;

	sendToTCP = true;
	pi->packet->extractData(0, Protocol::SIZE_NAME, roomNameSTR);
	roomName.assign(roomNameSTR);
	roomToJoin = sRm->getInstance()->getRoomByName(roomName);
	if (roomToJoin != NULL)
	{
		if (roomToJoin->getPlayersCount() != Protocol::DEFAULT_MAX_PLAYER_NUMBER)
		{
			Logger::logInfo("Le joueur " + pi->connexion->getLogin() + " se connecte a la room " + roomName + ".");
			/* Pour chacun des joueurs de la room, on crée des paquet de ROOM_DESCRIPTION. */
			bool success = roomToJoin->addClient(pi->connexion);
			Logger::logInfo("success = " + epi::toString(success));
			players = roomToJoin->getPlayersInRoom();
			for (auto it = players.begin(); it != players.end(); ++it)
			{
				api.connexion = (*it);
				api.packet = PacketFactory::createPacketRoomDescription(roomToJoin->getName(), roomToJoin->getMaxPlayerNumber(), roomToJoin->getPlayersCount() + 1, roomToJoin->getDifficulty(), roomToJoin->getIdMap());
				answer.push_back(api);
				playersName.push_back((*it)->getLogin());
			}
			/* Pour chacun des joueurs de la room, on crée des paquets ROOM_PLAYER_LIST. */
			
			for (auto it = players.begin(); it != players.end(); ++it)
			{
				api.connexion = (*it);
				api.packet = PacketFactory::createPacketRoomPlayerList(roomName, playersName);
				answer.push_back(api);
				Logger::logInfo("itering on " + api.connexion->getLogin());
			}
			
			api.connexion = pi->connexion;
			roomToJoin->addClient(pi->connexion);
			api.packet = PacketFactory::createPacketJoinRoomOk();
		}
		else if (roomToJoin->getState() == Room::RUNNING)
		{
			Logger::logInfo("La room " + roomName + " est en cours de partie.");
			api.connexion = pi->connexion;
			api.packet = PacketFactory::createPacketJoinRoomKo(Protocol::ROOM_IN_GAME);
		}
		else
		{
			Logger::logInfo("La room " + roomName + " n'est pas vide.");
			api.connexion = pi->connexion;
			api.packet = PacketFactory::createPacketJoinRoomKo(Protocol::ROOM_NOT_EMPTY);
		}
	}
	else
	{
		Logger::logInfo("La room " + roomName + " n'existe pas.");
		api.connexion = pi->connexion;
		api.packet = PacketFactory::createPacketJoinRoomKo(Protocol::ROOM_UNEXISTANT);
	}
	answer.push_back(api);
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_leaveRoom(PacketInfo *pi, bool &sendToTCP)
{
	PacketInfo					api;
	std::list<PacketInfo>		answer;
	Singleton<RoomManager>		*sRm = NULL;
	Room						*roomToLeave = NULL;
	std::list<Connexion*>		players;
	std::list<std::string>		playersName;

	sendToTCP = true;
	roomToLeave = sRm->getInstance()->getRoomByConnexion(pi->connexion);
	if (roomToLeave != NULL)
	{
		if (roomToLeave->removeClient(pi->connexion))
		{
			Logger::logInfo("Le client " + pi->connexion->getLogin() + " a bien quitté la room.");
			/* Pour chacun des joueurs de la room, on envoir un paquet ROOM_PLAYER_LIST. */
			players = roomToLeave->getPlayersInRoom();
			for (auto it = players.begin(); it != players.end(); ++it)
			{
				playersName.push_back((*it)->getLogin());
			}
			for (auto it = players.begin(); it != players.end(); ++it)
			{
				api.connexion = (*it);
				api.packet = PacketFactory::createPacketRoomPlayerList(roomToLeave->getName(), playersName);
				answer.push_back(api);
			}
			/* On crée le paquet pour le player qui quitte. */
			api.connexion = pi->connexion;
			api.packet = PacketFactory::createPacketLeaveRoomOk();
			/* Note: La room est automatiquement supprimée s'il n'y a plus de joueur dedans. */
		}
		else
		{
			Logger::logInfo("Le client " + pi->connexion->getLogin() + " n'a pas pu quitter la room.");
			api.connexion = pi->connexion;
			api.packet = PacketFactory::createPacketLeaveRoomKo(Protocol::ROOM_LEAVE_FAIL);
		}
	}
	else
	{
		Logger::logInfo("La room a quitter n'existe pas.");
		api.connexion = pi->connexion;
		api.packet = PacketFactory::createPacketLeaveRoomKo(Protocol::ROOM_UNEXISTANT);
	}
	answer.push_back(api);
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_launchGame(PacketInfo *pi, bool &sendToTCP)
{
	PacketInfo					api;
	std::list<PacketInfo>		answer;
	Singleton<RoomManager>		*sRm = NULL;
	Room						*roomToLaunch = NULL;
	std::string					roomName;
	char						roomNameSTR[Protocol::SIZE_NAME];
	std::list<Connexion*>		players;

	sendToTCP = true;
	api.connexion;
	pi->packet->extractData(0, Protocol::SIZE_NAME, roomNameSTR);
	roomName.assign(roomNameSTR);
	roomToLaunch = sRm->getInstance()->getRoomByName(roomName);
	players = roomToLaunch->getPlayersInRoom();
	if (roomToLaunch->getState() != Room::RUNNING)
	{
		Logger::logInfo("Creation des paquets pour les joueurs de la room \"" + roomName + "\".");
		for (auto it = players.begin(); it != players.end(); ++it)
		{
			api.connexion = (*it);
			api.packet = PacketFactory::createPacketLaunchGameOk();
			answer.push_back(api);
		}
		roomToLaunch->launchGame();
	}
	else
	{
		Logger::logInfo("La room \"" + roomName + "\" est deja en cours de jeu.");
		api.connexion = pi->connexion;
		api.packet = PacketFactory::createPacketLaunchGameKo(Protocol::ROOM_IN_GAME);
	}
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_movement(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;
	int		move = 0;
	Singleton<RoomManager>		*sRm = 0;
	Room*	room = 0;

	//Logger::logInfo("ActionManager::clt_movement!");

	pi->packet->extractData(0, sizeof(move), &move);

	room = sRm->getInstance()->getRoomByConnexion(pi->connexion);
	if (!room)
	{
		Logger::logInfo("error : client is not in a room!");
		return answer;
	}

	//Logger::logInfo("move : " + epi::toString<int>(move));

	Connexion*	tcpco = room->getConnexionByIpAddr(pi->connexion);

	if (!tcpco)
	{
		Logger::logInfo("invalid connexion in clt_movement!");
		return answer;
	}

	GameObject* go = room->getGame()->findGameObjectByTag("player_" + tcpco->getLogin());

	if (!go)
	{
		Logger::logInfo("invalid connexion in clt_movement! Couldnt find matching gameobject");
		return answer;
	}

	go->sendMessage(go, "move " + epi::toString<int>(move));
	Logger::logInfo("go : " + epi::toString<void*>(go));

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_shooting(PacketInfo *pi, bool &sendToTCP)
{
		std::list<PacketInfo>		answer;
	int		fire = 0;
	Singleton<RoomManager>		*sRm = 0;
	Room*	room = 0;

	pi->packet->extractData(0, sizeof(fire), &fire);

	room = sRm->getInstance()->getRoomByConnexion(pi->connexion);
	if (!room)
	{
		Logger::logInfo("error : client is not in a room!");
		return answer;
	}

	Connexion*	tcpco = room->getConnexionByIpAddr(pi->connexion);

	if (!tcpco)
	{
		Logger::logInfo("invalid connexion in clt_shooting!");
		return answer;
	}

	GameObject* go = room->getGame()->findGameObjectByTag("player_" + tcpco->getLogin());

	if (!go)
	{
		Logger::logInfo("invalid connexion in clt_shooting! Couldnt find matching gameobject");
		return answer;
	}

	go->sendMessage(go, "fire " + epi::toString<int>(fire));
	Logger::logInfo("go : " + epi::toString<void*>(go));

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_askDescribeEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_askPlayerScore(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::clt_askPlayerLife(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_authentificationOk(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_authentificationKo(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_roomDescription(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_createRoomOk(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_createRoomKo(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_joinRoomOk(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_joinRoomKo(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_leaveRoomOk(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_leaveRoomKo(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_launchGameOk(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_launchGameKo(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_startGame(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_spawnEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_destroyEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_moveEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_lifeEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_collision(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_descriptionEntity(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_entityScore(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_playerDisconnect(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}

std::list<PacketInfo>			ActionManager::srv_endGame(PacketInfo *pi, bool &sendToTCP)
{
	std::list<PacketInfo>		answer;

	sendToTCP = false;
	return (answer);
}
