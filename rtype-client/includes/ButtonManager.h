#ifndef __BUTTONMANAGER_H__
#define __BUTTONMANAGER_H__

#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include "Button.h"

class ButtonManager
{
public:
  ButtonManager();
  ~ButtonManager();

  void			addButton(std::string, Button::Action);
  void			clearButtons();
  int			getFocus();
  void setFocus(int);
  void			updateFocus(sf::Event);
  std::deque<Button *> &getButtons();
  float			getCurrentPosX();
  float			getCurrentPosY();
  void			Draw(sf::RenderWindow *);
  Button		*getFocusedButton();

private:
  std::deque<Button*>			buttons;
  float					CurrentPosX;
  float					CurrentPosY;
  int					CurrentFocus;
};

#endif /*__BUTTONMANAGER_H__*/
