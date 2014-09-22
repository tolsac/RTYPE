#include "ScreenManager.h"
#include <Scroller.h>
#include	<Game.h>

ScreenManager::ScreenManager(sf::RenderWindow *w)
{
	this->window = w;
}

ScreenManager::~ScreenManager()
{

}

void		ScreenManager::setWindow(sf::RenderWindow *w)
{
	this->window = w;
}

void ScreenManager::Draw()
{
	this->window->Clear();
	this->scr->Draw();
	if (this->state < 3)
	{
		this->menu->Draw(this->window);
	}
	else
		this->game->Draw(this->window);
	this->window->Display();
}

void ScreenManager::init()
{
	this->menu = new Menu(&this->state);
	this->game = new Game();
	this->scr = new Scroller(this->window);
	this->scr->init();
	this->menu->init();
	static_cast<Game*>(this->game)->init(this->getSoundManager());//->init();
	this->state = HOME;
	this->keyPosition = 0;
}

void ScreenManager::Clear()
{

}

void ScreenManager::run()
{
	sf::Event Event;

	this->getSoundManager().playMusicById(0);
	this->getSoundManager().playSoundById(SoundManager::INFO);
	this->window->EnableKeyRepeat(false);
	while (this->window->IsOpened())
	{
		if (this->window->GetEvent(Event))
		{
			this->updateEvent(Event);
			if (Event.Type == sf::Event::Closed)
				this->window->Close();
		}
		this->Draw();
	}
}

void ScreenManager::setState(int state)
{
	this->state = state;
}

int ScreenManager::getState()
{
	return (this->state);
}

IScreen *ScreenManager::getScreen() const
{
	if (this->state < 3)
		return (this->menu);
	return (this->game);
}

Scroller *ScreenManager::getScroller() const
{
	return this->scr;
}

void ScreenManager::setKeyPos(int pos)
{
	if (pos < 0)
		this->keyPosition = 0;
	else if (pos > 6)
		this->keyPosition = 6;
	else
		this->keyPosition = pos;
}

void ScreenManager::updateEvent(sf::Event Event)
{
  //this->input.Update(Event);
  if (this->state < 3)
  {
 	static_cast<Menu*>(this->menu)->updateEvent(Event, this->getSoundManager());
  }
  else
    static_cast<Game*>(this->game)->updateEvent(Event, this->getSoundManager());
}

SoundManager&		ScreenManager::getSoundManager()
{
	return this->soundmanager;
}