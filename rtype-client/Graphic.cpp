#include "Graphic.h"

Graphics::Graphics()
{}

Graphics::~Graphics()
{}

void				Graphics::init()
{
	this->sManager = new ScreenManager(this->window);
}

void				Graphics::operator()()
{
	this->run();
}

void				Graphics::setWindow(sf::RenderWindow *w)
{
	this->window = w;
}

void				Graphics::run()
{
	this->sManager->init();
	this->sManager->run();
}

ScreenManager			*Graphics::getScreenManager()
{
	return (this->sManager);
}
