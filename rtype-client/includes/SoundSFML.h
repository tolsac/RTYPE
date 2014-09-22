#pragma once

#include		"ISound.h"
#include		"SoundManager.h"

class			SoundSFML : public ISound
{
	sf::Sound	sound;
public:
	SoundSFML(void);
	~SoundSFML(void);
	virtual	bool	init(const std::string& name);
	virtual	bool	init(const sf::SoundBuffer& buffer);
	virtual void	play();
	virtual void	pause();
	virtual void	stop();
	virtual void	setVolume(float _volume);
};

