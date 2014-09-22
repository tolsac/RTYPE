#include "Button.h"

Button::Button(std::string str)
{
	sf::String Text;
	Text.SetText(str);
	this->Text = Text;
	this->ButtonPosX = 0.f;
	this->ButtonPosY = 0.f;
	this->isFocus = false;
}

Button::~Button()
{

}

void Button::setFocus(bool i)
{
	this->isFocus = i;
	if (this->isFocus == true)
		this->Text.SetStyle(sf::String::Underlined);
	else
		this->Text.SetStyle(sf::String::Regular);
}

sf::String Button::getButton()
{
	return (this->Text);
}

bool Button::getFocus()
{
	return (this->isFocus);
}

void Button::setTextButton(std::string str)
{
	this->Text.SetText(str);
}

std::string Button::getTextButton()
{
	return (this->Text.GetText());
}

void	Button::setPosX(float x)
{
	this->ButtonPosX = x;
}

void	Button::setPosY(float y)
{
	this->ButtonPosY = y;
}

void	Button::setPosition(float x, float y)
{
	this->setPosX(x);
	this->setPosY(y);
	sf::Vector2f pos(this->getPosX(), this->getPosY());
	this->Text.Move(pos);
}

float	Button::getPosX()
{
	return (this->ButtonPosX);
}

float	Button::getPosY()
{
	return (this->ButtonPosY);
}

float	Button::getSize()
{
	return (this->Text.GetSize());
}

void	Button::setAction(Action a)
{
  this->todo = a;
}

Button::Action	Button::getAction()
{
  return (this->todo);
}
