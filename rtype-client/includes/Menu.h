#ifndef __MENU_H__
#define __MENU_H__

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "IScreen.h"
#include "Singleton.hpp"
#include "ButtonManager.h"
#include "PacketFactory.h"
#include "NetworkManager.h"
#include "SoundManager.h"
class Menu : public IScreen
{
public:
  Menu(int*);
  ~Menu();

  virtual void		init();
  virtual void		Draw(sf::RenderWindow*);
  virtual void		Clear();
  virtual void		updateEvent(sf::Event&);
  virtual void		updateEvent(sf::Event&, SoundManager&);
  
  ButtonManager*	getButtonManager();

private:
  ButtonManager		*bManager;
  int			*SMState;
};

#endif /*__MENU_H__*/
