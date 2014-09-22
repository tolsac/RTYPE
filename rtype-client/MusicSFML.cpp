#include "MusicSFML.h"

MusicSFML::MusicSFML(void)
{
}


MusicSFML::~MusicSFML(void)
{
}

bool		MusicSFML::init(const std::string& name)
{
	if (!this->music.OpenFromFile(name))
        return false;
	this->music.SetVolume(10.0f);
	return true;
}

void		MusicSFML::play()
{
	if (this->music.GetStatus() == sf::Music::Playing)
		this->music.Pause();
	this->music.Play();
}

void		MusicSFML::pause()
{
	this->music.Pause();
}

void		MusicSFML::stop()
{
	this->music.Stop();
}

void		MusicSFML::setVolume(float _volume)
{
	if (_volume >= 0)
		this->music.SetVolume(_volume);
}