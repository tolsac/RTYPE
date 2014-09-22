#include "ButtonManager.h"

ButtonManager::ButtonManager()
{
	this->CurrentPosX = 0.0f;
	this->CurrentPosY = 0.0f;
	this->CurrentFocus = 0;
}

ButtonManager::~ButtonManager()
{

}

float	ButtonManager::getCurrentPosX()
{
  return (this->CurrentPosX);
}

float ButtonManager::getCurrentPosY()
{
  float y = 0.0;
	
  if (this->buttons.size() > 0)
    y = this->buttons.back()->getPosY() + this->buttons.back()->getSize() + 10;
  else
    y = 0.0f;
  return (y);
}

void ButtonManager::addButton(std::string str, Button::Action a)
{
  Button	*b;

  b = new Button(str);
  b->setPosition(this->getCurrentPosX(), this->getCurrentPosY());
  b->setAction(a);
  if (this->buttons.size() == 0)
    b->setFocus(true);
  this->buttons.push_back(b); 
}

void ButtonManager::setFocus(int i)
{
	this->CurrentFocus = i;
}

void ButtonManager::clearButtons()
{
  this->buttons.clear();
}

void				ButtonManager::updateFocus(sf::Event Event)
{
	std::cout << "button : " << CurrentFocus <<std::endl;
	if (this->CurrentFocus >= (int) this->buttons.size())
		this->CurrentFocus = 0;
  this->buttons[this->CurrentFocus]->setFocus(false);
  if (Event.Key.Code == sf::Key::Down)
    this->CurrentFocus = (this->CurrentFocus + 1) % this->buttons.size();
  else if (Event.Key.Code == sf::Key::Up)
    if (this->CurrentFocus == 0)
      this->CurrentFocus = this->buttons.size() - 1;
    else
      this->CurrentFocus = (this->CurrentFocus - 1) % this->buttons.size();
  this->buttons[this->CurrentFocus]->setFocus(true);
}

int					ButtonManager::getFocus()
{
  return (this->CurrentFocus);
}

std::deque<Button *> &ButtonManager::getButtons()
{
	return (this->buttons);
}

void ButtonManager::Draw(sf::RenderWindow *Window)
{	
	/*
  std::deque<Button *>::iterator it;
  std::cout << "e" << std::endl;
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    Window->Draw((*it)->getButton());
std::cout << "s" << std::endl;
  */
	unsigned int i = -1;
	sf::String b;

	while (++i < this->buttons.size())
	{
		b = this->buttons[i]->getButton();
		b.SetX(b.GetPosition().x + Window->GetView().GetRect().Left + 100 * Window->GetFrameTime());
		Window->Draw(b);
	}	
}



Button		*ButtonManager::getFocusedButton()
{
  return (this->buttons[this->CurrentFocus]);
}
