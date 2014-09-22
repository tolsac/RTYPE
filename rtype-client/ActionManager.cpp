/*
** ActionManager.cpp for ActionManager in /home/tolsa/rtype-2015-tolsa_c/rtype-client
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Sat Jan 12 07:15:46 2013 tolsa_c
** Last update Sun Jan 20 03:37:26 2013 tolsa_c
*/

#include <ActionManager.h>
#include <ScreenManager.h>
#include <Button.h>
#include <iostream>
#include <Client.h>

ActionManager::ActionManager()
{
	this->actions.insert(std::make_pair(Protocol::AUTHENTIFICATION_OK, &ActionManager::ans_authentificationOk));
	this->actions.insert(std::make_pair(Protocol::AUTHENTIFICATION_KO, &ActionManager::ans_authentificationKo));
	this->actions.insert(std::make_pair(Protocol::ROOM_DESCRIPTION, &ActionManager::ans_roomDescription));
	this->actions.insert(std::make_pair(Protocol::ROOM_PLAYER_LIST, &ActionManager::ans_roomPlayerList));
	this->actions.insert(std::make_pair(Protocol::CREATE_ROOM_OK, &ActionManager::ans_createRoomOk));
	this->actions.insert(std::make_pair(Protocol::CREATE_ROOM_KO, &ActionManager::ans_createRoomKo));
	this->actions.insert(std::make_pair(Protocol::JOIN_ROOM_OK, &ActionManager::ans_joinRoomOk));
	this->actions.insert(std::make_pair(Protocol::JOIN_ROOM_KO, &ActionManager::ans_joinRoomKo));
	this->actions.insert(std::make_pair(Protocol::LEAVE_ROOM_OK, &ActionManager::ans_leaveRoomOk));
	this->actions.insert(std::make_pair(Protocol::LEAVE_ROOM_KO, &ActionManager::ans_leaveRoomKo));
	this->actions.insert(std::make_pair(Protocol::LAUNCH_GAME_OK, &ActionManager::ans_launchGameOk));
	this->actions.insert(std::make_pair(Protocol::LAUNCH_GAME_KO, &ActionManager::ans_launchGameKo));

	this->actions.insert(std::make_pair(Protocol::START_GAME, &ActionManager::ans_startGame));
	this->actions.insert(std::make_pair(Protocol::SPAWN_ENTITY, &ActionManager::ans_spawnEntity));
	this->actions.insert(std::make_pair(Protocol::DESTROY_ENTITY, &ActionManager::ans_destroyEntity));
	this->actions.insert(std::make_pair(Protocol::MOVE_ENTITY, &ActionManager::ans_moveEntity));
	this->actions.insert(std::make_pair(Protocol::LIFE_ENTITY, &ActionManager::ans_lifeEntity));
	this->actions.insert(std::make_pair(Protocol::COLLISION, &ActionManager::ans_collision));
	this->actions.insert(std::make_pair(Protocol::DESCRIPTION_ENTITY, &ActionManager::ans_descriptionEntity));
	this->actions.insert(std::make_pair(Protocol::ENTITY_SCORE, &ActionManager::ans_entityScore));
	this->actions.insert(std::make_pair(Protocol::PLAYER_DISCONNECT, &ActionManager::ans_playerDisconnect));
	this->actions.insert(std::make_pair(Protocol::END_GAME, &ActionManager::ans_endGame));  
}

ActionManager::~ActionManager()
{}

void			ActionManager::setSM(ScreenManager *s)
{
	this->sManager = s;
}

void			ActionManager::doAction(PacketContainer *pi)
{
  //  std::cout << "doAction(" << pi->getCommandID() << ")"<<std::endl;
	((*this).*actions[pi->getCommandID()])(pi);
	//  pi->displayPacket();
}

void           ActionManager::ans_authentificationOk(PacketContainer *pi)
{

}

void           ActionManager::ans_authentificationKo(PacketContainer *pi)
{
	this->sManager->setState(HOME);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Auth failure (exit?)", Button::EXIT);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->setFocus(0);

}

void           ActionManager::ans_roomDescription(PacketContainer *pi)
{
	if (this->sManager->getState() != LIST_ROOM)
	{
		static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
		static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Retour", Button::RETURN);
		static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->setFocus(0);
	}
	this->sManager->setState(LIST_ROOM);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton(pi->getData(), Button::ENTER_ROOM);
}

void           ActionManager::ans_roomPlayerList(PacketContainer *pi)
{
  char		*room;
  std::string   cmp;
  int		nbplayerz;
  int		i;
  
  room = new char[Protocol::SIZE_NAME];
  std::cout << "ROOM LIST PLAYER" << room << std::endl;
  this->sManager->setState(IN_ROOM);
  if (this->sManager->getState() == IN_ROOM)
    {
      pi->extractData(0, Protocol::SIZE_NAME, room);
      cmp.assign(room);
      if (cmp == Client::roomName)
	{
	  static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	  nbplayerz = ((pi->getSizeData() - Protocol::SIZE_NAME) / Protocol::SIZE_NAME);
	  i = 0;
	  while (++i <= nbplayerz)
	    {
	      memset(room, 0, Protocol::SIZE_NAME);
	      pi->extractData(Protocol::SIZE_NAME * i, Protocol::SIZE_NAME, room);
	      std::cout << "ROOM LIST PLAYER :: NEW ENTRANCE --> " << room << std::endl;
	      cmp.assign(room);
	      if (cmp != "")
		static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton(room, Button::NONE);
	    }	
	}
      static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Launch Game", Button::ENTER_GAME); 
      static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Retour", Button::LEAVE_ROOM); 
    }
}

void           ActionManager::ans_createRoomOk(PacketContainer *pi)
{
	this->sManager->setState(IN_ROOM);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton(Client::login, Button::NONE); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Launch Game", Button::ENTER_GAME); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Retour", Button::LEAVE_ROOM); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->setFocus(0);
}

void           ActionManager::ans_createRoomKo(PacketContainer *pi)
{
	this->sManager->setState(HOME);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Retour", Button::RETURN); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Create room failure 'Room alreay exists' (exit?)", Button::EXIT);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->setFocus(0);
}

void           ActionManager::ans_joinRoomOk(PacketContainer *pi)
{
	this->sManager->setState(IN_ROOM);
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton("Retour", Button::LEAVE_ROOM); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->addButton(Client::login, Button::NONE); 
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->setFocus(0);
}

void           ActionManager::ans_joinRoomKo(PacketContainer *pi)
{
	std::cout << "join room ko" << std::endl;
}

void           ActionManager::ans_leaveRoomOk(PacketContainer *pi)
{
	this->sManager->setState(HOME);
	std::cout << "leave room ok" << std::endl;
	static_cast<Menu*>(this->sManager->getScreen())->getButtonManager()->clearButtons();
	static_cast<Menu*>(this->sManager->getScreen())->init();
}

void           ActionManager::ans_leaveRoomKo(PacketContainer *pi)
{
	std::cout << "leave room ko" << std::endl;
}

void           ActionManager::ans_launchGameOk(PacketContainer *pi)
{
	this->sManager->getScroller()->reset();
}

void           ActionManager::ans_launchGameKo(PacketContainer *pi)
{
}

void           ActionManager::ans_startGame(PacketContainer *pi)
{
}

void           ActionManager::ans_spawnEntity(PacketContainer *pi)
{
	int idEntity;
	int idType;
	int posX;
	int posY;

	this->sManager->setState(IN_GAME);
	pi->extractData(0, sizeof(int), &idEntity);
	pi->extractData(sizeof(int), sizeof(int), &idType);
	pi->extractData(sizeof(int) * 2, sizeof(int), &posX);
	pi->extractData(sizeof(int) * 3, sizeof(int), &posY);

	this->sManager->setState(IN_GAME);

	std::cout << "spawning entity idEntity = " << idEntity << " idType" << idType << std::endl;
	std::cout << "pos x = " << posX << "    pos y = " << posY << std::endl;
	sf::Image *img = static_cast<Game*>(this->sManager->getScreen())->getRessources()[idType];
	static_cast<Game*>(this->sManager->getScreen())->getEntityManager().addEntity(idEntity, idType, (float) posX, (float) posY, img);
}

void           ActionManager::ans_destroyEntity(PacketContainer *pi)
{
	int idEntity;

	pi->extractData(0, sizeof(int), &idEntity);
	std::cout << "<destroy entity>" << std::endl;
	static_cast<Game*>(this->sManager->getScreen())->getEntityManager().deleteEntity(idEntity);
	std::cout << "</destroy entity>" << std::endl;
}

void           ActionManager::ans_moveEntity(PacketContainer *pi)
{
	int idEntity;
	int posX;
	int posY;
	int moveType;

	pi->extractData(0, sizeof(int), &idEntity);
	pi->extractData(sizeof(int), sizeof(int), &posX);
	pi->extractData(sizeof(int) * 2, sizeof(int), &posY);
	pi->extractData(sizeof(int) * 3, sizeof(int), &moveType);
	static_cast<Game*>(this->sManager->getScreen())->getEntityManager().moveEntity(idEntity, posX, posY);
}

void           ActionManager::ans_lifeEntity(PacketContainer *pi)
{
}

void           ActionManager::ans_collision(PacketContainer *pi)
{
}

void           ActionManager::ans_descriptionEntity(PacketContainer *pi)
{
}

void           ActionManager::ans_entityScore(PacketContainer *pi)
{
}

void           ActionManager::ans_playerDisconnect(PacketContainer *pi)
{
}

void           ActionManager::ans_endGame(PacketContainer *pi)
{
}



