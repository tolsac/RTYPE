#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include <Menu.h>
#include "InputManager.h"
#include "EntityManager.h"
#include "Game.h"
#include "Scroller.h"
#include "SoundManager.h"

class Scroller;

enum ScreenState
{
	HOME,
	LIST_ROOM,
	IN_ROOM,
	IN_GAME
};

class ScreenManager
{
public:
  ScreenManager(sf::RenderWindow*);
  ~ScreenManager();

  void			init();
  void			Draw();
  void			Clear();
  void			run();
  int			getState();
  void			setState(int state);
  int			getKeyPos();
  void			setKeyPos(int i);
  void			updateEvent(sf::Event Event);
  IScreen		*getScreen() const;
  Scroller		*getScroller() const;
  EntityManager		myEntities;
  void			setWindow(sf::RenderWindow*);
  SoundManager&	getSoundManager();

private:
  IScreen	      	*menu;
  IScreen     		*game;
  int			state;
  int			keyPosition;
  InputManager		input;
  sf::RenderWindow     	*window;
  SoundManager		soundmanager;
  Scroller		*scr;
};

#endif /*__SCREENMANAGER_H__*/
