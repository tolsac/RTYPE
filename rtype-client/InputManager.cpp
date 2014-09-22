#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::Update(sf::Event Event)
{
	this->Event = Event;
}

sf::Event InputManager::getEvent()
{
	return (this->Event);
}