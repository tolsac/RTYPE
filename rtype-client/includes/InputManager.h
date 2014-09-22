#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update(sf::Event Event);
	sf::Event getEvent();
private:
	sf::Event Event;
};

#endif /*__INPUTMANAGER_H__*/