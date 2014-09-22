/* Header de la classe Protocol. */
/* Auteur: Bertrand Boyer */
/* Commence le 22/12/12. */
/* Derniere modification: 23/12/12. */

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <map>
#include <stdint.h>

class Protocol
{
private:
	/* Méthodes. */
	static std::map<int, size_t>		initMapSize(void);			/* Initialise la map des tailles. */
	static std::map<int, std::string>	initMapMessages(void);			/* Initialise la map des messages. */
	static std::map<int, std::string>	initMapCommandName(void);		/* Initialise la map du nom des commandes. */

public:
	/* Variables. */
	static const uint32_t						MAGIC = 1887007858;			/* Nombre magic. */
	static const int							SIZE = 256;			/* Taille du buffer de data. */
	static const int							SIZE_NAME = 32;		/* Taille des logins/noms. */
	const static int							DEFAULT_MAX_PLAYER_NUMBER = 4;	/* Nombre max de joueurs par room. */
	static const std::map<int, size_t>			mapSize;			/* Map des tailles de data en fonction des actions. */
	static const std::map<int, std::string>		mapMessages;		/* Map des messages. */
	static const std::map<int, std::string>		mapCommandName;		/* Map des noms de commandes. */

	/* Liste des actions hors game du client. */
	enum eClientActionTCP
	{
		AUTHENTIFICATION = 0,			/* Le client s’authentifie. */
		SHOW_ROOM,						/* Requête de la liste des rooms. */
		CREATE_ROOM,					/* Création d’une room sur le serveur. */
		JOIN_ROOM,						/* Rejoindre une room. */
		LEAVE_ROOM,						/* Quitter une room. */
		LAUNCH_GAME,					/* Lancer une partie (depuis une room). */
		MAX_CLIENT_ACTION_TCP			/* Toujours en dernier. */
	};

	/* Liste des actions in game du client. */
	enum eClientActionUDP
	{
		MOVEMENT = 100,					/* Déplacement du joueur. */
		SHOOTING,						/* Le joueur tire. */
		ASK_DESCRIBE_ENTITY,			/* Demande de description d’une entité. */
		ASK_PLAYER_SCORE,				/* Demande du score d’un joueur. */
		ASK_PLAYER_LIFE,				/* Demande de la vie d’un joueur. */
		MAX_CLIENT_ACTION_UDP			/* Toujours en dernier. */
	};

	/* Liste des actions hors game du serveur. */
	enum eServerActionTCP
	{
		AUTHENTIFICATION_OK = 200,		/* Succès de l’authentification. */
		AUTHENTIFICATION_KO,			/* Echec de l’authentification. */
		ROOM_DESCRIPTION,				/* Description de la room. */
		ROOM_PLAYER_LIST,				/* Liste des joueurs de la room. */
		CREATE_ROOM_OK,					/* Succès de la création de room. */
		CREATE_ROOM_KO,					/* Echec de la création de la room. */
		JOIN_ROOM_OK,					/* Succès de l’accès à la room. */
		JOIN_ROOM_KO,					/* Echec de l’accès à la room. */
		LEAVE_ROOM_OK,					/* Succès du leaving room. */
		LEAVE_ROOM_KO,					/* Echec lors du leave room. */
		LAUNCH_GAME_OK,					/* Succès du lancement du jeu. */
		LAUNCH_GAME_KO,					/* Echec du lancement du jeu. */
		MAX_SERVER_ACTION_TCP			/* Toujours en dernier. */
	};

	/* Liste des actions in game du serveur. */
	enum eServerActionUDP
	{
		START_GAME = 300,				/* Début de la partie. */
		SPAWN_ENTITY,					/* Apparition d’une entité */
		DESTROY_ENTITY,					/* Destruction d’une entité. */
		MOVE_ENTITY,					/* Déplacement d’une entité. */
		LIFE_ENTITY,					/* Quantité de vie d’une entité. */
		COLLISION,						/* Collision entre 2 entité. */
		DESCRIPTION_ENTITY,				/* Description d’une entité. */
		ENTITY_SCORE,					/* Score du joueur. */
		PLAYER_DISCONNECT,				/* Déconnexion d’un joueur. */
		END_GAME,						/* Fin de la partie. */
		MAX_SERVER_ACTION_UDP			/* Toujours en dernier. */
	};

	/* Liste des tailles de chacunes des actions. */
	enum eSizeActions
	{
		SIZE_AUTHENTIFICATION = SIZE_NAME,
		SIZE_SHOW_ROOM = 0,
		SIZE_CREATE_ROOM = SIZE_NAME + 3 * sizeof(int),
		SIZE_JOIN_ROOM = SIZE_NAME,
		SIZE_LEAVE_ROOM = 0,
		SIZE_LAUNCH_GAME = SIZE_NAME,

		SIZE_MOVEMENT = sizeof(int),
		SIZE_SHOOTING = sizeof(int),
		SIZE_ASK_DESCRIBE_ENTITY = sizeof(int),
		SIZE_ASK_PLAYER_SCORE = sizeof(int),
		SIZE_ASK_PLAYER_LIFE = sizeof(int),

		SIZE_AUTHENTIFICATION_OK = 0,
		SIZE_AUTHENTIFICATION_KO = sizeof(int),
		SIZE_ROOM_DESCRIPTION = SIZE_NAME + 4 * sizeof(int),
		SIZE_ROOM_PLAYER_LIST = 5 * SIZE_NAME,
		SIZE_CREATE_ROOM_OK = 0,
		SIZE_CREATE_ROOM_KO = sizeof(int),
		SIZE_JOIN_ROOM_OK = 0,
		SIZE_JOIN_ROOM_KO = sizeof(int),
		SIZE_LEAVE_ROOM_OK = 0,
		SIZE_LEAVE_ROOM_KO = sizeof(int),
		SIZE_LAUNCH_GAME_OK = 0,
		SIZE_LAUNCH_GAME_KO = sizeof(int),

		SIZE_START_GAME = 0,
		SIZE_SPAWN_ENTITY = 4 * sizeof(int),
		SIZE_DESTROY_ENTITY = sizeof(int),
		SIZE_MOVE_ENTITY = 4 * sizeof(int),
		SIZE_LIFE_ENTITY = 2 * sizeof(int),
		SIZE_COLLISION = 2 * sizeof(int),
		SIZE_DESCRIPTION_ENTITY = 5 * sizeof(int),
		SIZE_ENTITY_SCORE = 2 * sizeof(int),
		SIZE_PLAYER_DISCONNECT = sizeof(int),
		SIZE_END_GAME = sizeof(int)
	};

	/* Liste des différents messages possibles. */
	enum eMessage
	{
		/* Cette partie concerne les messages d’erreurs. */
		LOGIN_ALREADY_EXISTS = 0,		/* Le login existe déjà. */
		BAD_LOGIN,						/* Le login n’est pas bon (caractère interdit). */
		ROOM_ALREADY_EXISTS,			/* Le nom de la room existe déjà. */
		ROOM_UNEXISTANT,				/* La room n'existe pas. */
		ROOM_NOT_EMPTY,					/* Rejoindre une room pleine. */
		ROOM_IN_GAME,					/* La room est en cours de partie. */
		ROOM_KICK,						/* Le joueur est éjecté de la room. */
		ROOM_LEAVE_FAIL,				/* Le joueur n'a pas pu quitter la room. */
		LAUNCH_FAIL,					/* Si on essaye de lancer un game avec 1 joueur. */

		/* Cette partie contient les messages d’infos. */
		ALL_PLAYER_DISCONNECTED,		/* Il reste 1 joueur sur la map --> end game */
		VICTORY,						/* Victoire d’un jouer --> end game */
		LOOSER							/* Le joueur a perdu --> end game. */
	};

	/* Liste des mouvements possibles. */
	enum eMovement
	{
		MOVE_UP = 0,					/* Direction haut. */
		MOVE_UP_RIGHT,					/* Direction haut-droite. */
		MOVE_RIGHT,						/* Direction droite. */
		MOVE_DOWN_RIGHT,				/* Derection bas-broite. */
		MOVE_DOWN,						/* Direction bas. */
		MOVE_DOWN_LEFT,					/* Direction bas-gauche. */
		MOVE_LEFT,						/* Direction gauche. */
		MOVE_UP_LEFT,					/* Direction haut-gauche. */
		SHOOT
	};

	/* Liste des difficultés. */
	enum eDifficulty
	{
		EASY_MODE = 0,
		MEDIUM_MODE,
		HARD_MODE,
		CHUCK_NORRIS_MODE,
		GOD_MODE
	};

	/* Liste des maps. */
	enum eMap
	{
		MAP1 = 0,
		MAP2,
		MAP3
	};
};

#endif /* __PROTOCOL_H__ */
