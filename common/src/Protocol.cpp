/* Auteur: Bertrand Boyer */
/* Commence le 22/12/12. */
/* Derniere modification: 14/01/13. */

#include <Protocol.h>

const std::map<int, size_t> Protocol::mapSize = Protocol::initMapSize();
const std::map<int, std::string> Protocol::mapMessages = Protocol::initMapMessages();
const std::map<int, std::string> Protocol::mapCommandName = Protocol::initMapCommandName();

std::map<int, size_t>			Protocol::initMapSize(void)
{
	std::map<int, size_t>		mapSize;

	mapSize.insert(std::make_pair(AUTHENTIFICATION, SIZE_AUTHENTIFICATION));
	mapSize.insert(std::make_pair(SHOW_ROOM, SIZE_SHOW_ROOM));
	mapSize.insert(std::make_pair(CREATE_ROOM, SIZE_CREATE_ROOM));
	mapSize.insert(std::make_pair(JOIN_ROOM, SIZE_JOIN_ROOM));
	mapSize.insert(std::make_pair(LEAVE_ROOM, SIZE_LEAVE_ROOM));
	mapSize.insert(std::make_pair(LAUNCH_GAME, SIZE_LAUNCH_GAME));

	mapSize.insert(std::make_pair(MOVEMENT, SIZE_MOVEMENT));
	mapSize.insert(std::make_pair(SHOOTING, SIZE_SHOOTING));
	mapSize.insert(std::make_pair(ASK_DESCRIBE_ENTITY, SIZE_ASK_DESCRIBE_ENTITY));
	mapSize.insert(std::make_pair(ASK_PLAYER_SCORE, SIZE_ASK_PLAYER_SCORE));
	mapSize.insert(std::make_pair(ASK_PLAYER_LIFE, SIZE_ASK_PLAYER_LIFE));

	mapSize.insert(std::make_pair(AUTHENTIFICATION_OK, SIZE_AUTHENTIFICATION_OK));
	mapSize.insert(std::make_pair(AUTHENTIFICATION_KO, SIZE_AUTHENTIFICATION_KO));
	mapSize.insert(std::make_pair(ROOM_DESCRIPTION, SIZE_ROOM_DESCRIPTION));
	mapSize.insert(std::make_pair(ROOM_PLAYER_LIST, SIZE_ROOM_PLAYER_LIST));
	mapSize.insert(std::make_pair(CREATE_ROOM_OK, SIZE_CREATE_ROOM_OK));
	mapSize.insert(std::make_pair(CREATE_ROOM_KO, SIZE_CREATE_ROOM_KO));
	mapSize.insert(std::make_pair(JOIN_ROOM_OK, SIZE_JOIN_ROOM_OK));
	mapSize.insert(std::make_pair(JOIN_ROOM_KO, SIZE_JOIN_ROOM_KO));
	mapSize.insert(std::make_pair(LEAVE_ROOM_OK, SIZE_LEAVE_ROOM_OK));
	mapSize.insert(std::make_pair(LEAVE_ROOM_KO, SIZE_LEAVE_ROOM_KO));
	mapSize.insert(std::make_pair(LAUNCH_GAME_OK, SIZE_LAUNCH_GAME_OK));
	mapSize.insert(std::make_pair(LAUNCH_GAME_KO, SIZE_LAUNCH_GAME_KO));

	mapSize.insert(std::make_pair(START_GAME, SIZE_START_GAME));
	mapSize.insert(std::make_pair(SPAWN_ENTITY, SIZE_SPAWN_ENTITY));
	mapSize.insert(std::make_pair(DESTROY_ENTITY, SIZE_DESTROY_ENTITY));
	mapSize.insert(std::make_pair(MOVE_ENTITY, SIZE_MOVE_ENTITY));
	mapSize.insert(std::make_pair(LIFE_ENTITY, SIZE_LIFE_ENTITY));
	mapSize.insert(std::make_pair(COLLISION, SIZE_COLLISION));
	mapSize.insert(std::make_pair(DESCRIPTION_ENTITY, SIZE_DESCRIPTION_ENTITY));
	mapSize.insert(std::make_pair(ENTITY_SCORE, SIZE_ENTITY_SCORE));
	mapSize.insert(std::make_pair(PLAYER_DISCONNECT, SIZE_PLAYER_DISCONNECT));
	mapSize.insert(std::make_pair(END_GAME, SIZE_END_GAME));

	return (mapSize);
}

std::map<int, std::string>			Protocol::initMapMessages(void)
{
	std::map<int, std::string>		mapMessages;

	mapMessages.insert(std::make_pair(LOGIN_ALREADY_EXISTS, "Le login existe déjà."));
	mapMessages.insert(std::make_pair(BAD_LOGIN, "Mauvais login"));
	mapMessages.insert(std::make_pair(ROOM_ALREADY_EXISTS, "Cette room existe déjà."));
	mapMessages.insert(std::make_pair(ROOM_UNEXISTANT, "Cette room n'existe pas."));
	mapMessages.insert(std::make_pair(ROOM_NOT_EMPTY, "Cette room est déjà pleine."));
	mapMessages.insert(std::make_pair(ROOM_IN_GAME, "Cette room est en cours de jeu."));
	mapMessages.insert(std::make_pair(ROOM_KICK, "Vous avez été kick."));
	mapMessages.insert(std::make_pair(ROOM_LEAVE_FAIL, "Vous n'avez pas pu quitter la room."));
	mapMessages.insert(std::make_pair(LAUNCH_FAIL, "Il n'y a pas assez de joueurs."));

	mapMessages.insert(std::make_pair(ALL_PLAYER_DISCONNECTED, "Vous êtes le dernier joueur."));
	mapMessages.insert(std::make_pair(VICTORY, "Vous avez gagné !"));
	mapMessages.insert(std::make_pair(LOOSER, "Vous avez perdu..."));

	return (mapMessages);
}

std::map<int, std::string>			Protocol::initMapCommandName(void)
{
	std::map<int, std::string>		mapCommandName;

	mapCommandName.insert(std::make_pair(AUTHENTIFICATION, "AUTHENTIFICATION"));
	mapCommandName.insert(std::make_pair(SHOW_ROOM, "SHOW_ROOM"));
	mapCommandName.insert(std::make_pair(CREATE_ROOM, "CREATE_ROOM"));
	mapCommandName.insert(std::make_pair(JOIN_ROOM, "JOIN_ROOM"));
	mapCommandName.insert(std::make_pair(LEAVE_ROOM, "LEAVE_ROOM"));
	mapCommandName.insert(std::make_pair(LAUNCH_GAME, "LAUNCH_GAME"));

	mapCommandName.insert(std::make_pair(MOVEMENT, "MOVEMENT"));
	mapCommandName.insert(std::make_pair(SHOOTING, "SHOOTING"));
	mapCommandName.insert(std::make_pair(ASK_DESCRIBE_ENTITY, "ASK_DESCRIBE_ENTITY"));
	mapCommandName.insert(std::make_pair(ASK_PLAYER_SCORE, "ASK_PLAYER_SCORE"));
	mapCommandName.insert(std::make_pair(ASK_PLAYER_LIFE, "ASK_PLAYER_LIFE"));

	mapCommandName.insert(std::make_pair(AUTHENTIFICATION_OK, "AUTHENTIFICATION_OK"));
	mapCommandName.insert(std::make_pair(AUTHENTIFICATION_KO, "AUTHENTIFICATION_KO"));
	mapCommandName.insert(std::make_pair(ROOM_DESCRIPTION, "ROOM_DESCRIPTION"));
	mapCommandName.insert(std::make_pair(ROOM_PLAYER_LIST, "ROOM_PLAYER_LIST"));
	mapCommandName.insert(std::make_pair(CREATE_ROOM_OK, "CREATE_ROOM_OK"));
	mapCommandName.insert(std::make_pair(CREATE_ROOM_KO, "CREATE_ROOM_KO"));
	mapCommandName.insert(std::make_pair(JOIN_ROOM_OK, "JOIN_ROOM_OK"));
	mapCommandName.insert(std::make_pair(JOIN_ROOM_KO, "JOIN_ROOM_KO"));
	mapCommandName.insert(std::make_pair(LEAVE_ROOM_OK, "LEAVE_ROOM_OK"));
	mapCommandName.insert(std::make_pair(LEAVE_ROOM_KO, "LEAVE_ROOM_KO"));
	mapCommandName.insert(std::make_pair(LAUNCH_GAME_OK, "LAUNCH_GAME_OK"));
	mapCommandName.insert(std::make_pair(LAUNCH_GAME_KO, "LAUNCH_GAME_KO"));

	mapCommandName.insert(std::make_pair(START_GAME, "START_GAME"));
	mapCommandName.insert(std::make_pair(SPAWN_ENTITY, "SPAWN_ENTITY"));
	mapCommandName.insert(std::make_pair(DESTROY_ENTITY, "DESTROY_ENTITY"));
	mapCommandName.insert(std::make_pair(MOVE_ENTITY, "MOVE_ENTITY"));
	mapCommandName.insert(std::make_pair(LIFE_ENTITY, "LIFE_ENTITY"));
	mapCommandName.insert(std::make_pair(COLLISION, "COLLISION"));
	mapCommandName.insert(std::make_pair(DESCRIPTION_ENTITY, "DESCRIPTION_ENTITY"));
	mapCommandName.insert(std::make_pair(ENTITY_SCORE, "ENTITY_SCORE"));
	mapCommandName.insert(std::make_pair(PLAYER_DISCONNECT, "PLAYER_DISCONNECT"));
	mapCommandName.insert(std::make_pair(END_GAME, "END_GAME"));

	return (mapCommandName);
}