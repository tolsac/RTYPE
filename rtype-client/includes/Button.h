#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
   enum Action
     {
       CREATE_ROOM,     //idem a ENTER_ROOM_LIST + envoi packet creation room                            
       ENTER_ROOM_LIST, //balance l'affichage de la liste des rooms                                      
       ENTER_ROOM,      //balance l'affichage d'une room (mode in_room)                                  
       ENTER_GAME, //balance l'affichage du jeu
	   LEAVE_ROOM,
       EXIT,            //exit le jeu                                                                    
       RETURN,
	   NONE
     };

  Button() {};
  Button(std::string str);
  ~Button();

  void		setFocus(bool i);
  bool		getFocus();
  sf::String   	getButton();
  void		setTextButton(std::string str);
  std::string	getTextButton();
  void		setPosX(float x);
  void		setPosY(float y);
  void		setPosition(float x, float y);
  float		getPosX();
  float		getPosY();
  float		getSize();
  void		setAction(Action);
  Button::Action	getAction();

private:
  sf::String	Text;
  bool		isFocus;
  float		ButtonPosX;
  float		ButtonPosY;
  Button::Action	todo;
};

#endif /*__BUTTON_H__*/
