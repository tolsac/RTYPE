#include "SoundSFML.h"


SoundSFML::SoundSFML(void)
{
}

SoundSFML::~SoundSFML(void)
{
}

bool		SoundSFML::init(const std::string& name)
{
	sf::SoundBuffer	tmp;

	if (!tmp.LoadFromFile(name))
        return false;
	this->sound.SetBuffer(tmp);
	return true;
}

bool		SoundSFML::init(const sf::SoundBuffer& buffer)
{
	this->sound.SetBuffer(buffer);
	return true;
}

void		SoundSFML::play()
{
	if (this->sound.GetStatus() == sf::Sound::Playing)
		this->sound.Pause();
	this->sound.Play();
}

void		SoundSFML::pause()
{
	this->sound.Pause();
}

void		SoundSFML::stop()
{
	this->sound.Stop();
}

void		SoundSFML::setVolume(float _volume)
{
	if (_volume >= 0)
		this->sound.SetVolume(_volume);
}