/*
** ActionManager.h for ActionManager in /home/tolsa/rtype-2015-tolsa_c/rtype-client/includes
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Sat Jan 12 04:04:03 2013 tolsa_c
** Last update Sat Jan 19 23:37:05 2013 tolsa_c
*/

#ifndef ACTIONMANAGER_H_
# define ACTIONMANAGER_H_

#include <list>
#include <map>

#include <PacketContainer.h>
//#include <ScreenManager.h>

class ScreenManager;

class ActionManager
{
public:
  ActionManager();
  ~ActionManager();

  void    	 doAction(PacketContainer*);
  void		 setSM(ScreenManager*);
private:
  typedef void	 (ActionManager::*fct)(PacketContainer*);
  std::map<int, fct>		  actions;
  ScreenManager			  *sManager;

  void           ans_authentificationOk(PacketContainer *pi);
  void           ans_authentificationKo(PacketContainer *pi);
  void           ans_roomDescription(PacketContainer *pi);
  void           ans_roomPlayerList(PacketContainer *pi);
  void           ans_createRoomOk(PacketContainer *pi);
  void           ans_createRoomKo(PacketContainer *pi);
  void           ans_joinRoomOk(PacketContainer *pi);
  void           ans_joinRoomKo(PacketContainer *pi);
  void           ans_leaveRoomOk(PacketContainer *pi);
  void           ans_leaveRoomKo(PacketContainer *pi);
  void           ans_launchGameOk(PacketContainer *pi);
  void           ans_launchGameKo(PacketContainer *pi);

  void           ans_startGame(PacketContainer *pi);
  void           ans_spawnEntity(PacketContainer *pi);
  void           ans_destroyEntity(PacketContainer *pi);
  void           ans_moveEntity(PacketContainer *pi);
  void           ans_lifeEntity(PacketContainer *pi);
  void           ans_collision(PacketContainer *pi);
  void           ans_descriptionEntity(PacketContainer *pi);
  void           ans_entityScore(PacketContainer *pi);
  void           ans_playerDisconnect(PacketContainer *pi);
  void           ans_endGame(PacketContainer *pi);
};

#endif /* !ACTIONMANAGER_H_ */
