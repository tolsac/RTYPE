#pragma once

#include			"IMusic.h"
#include			"SoundManager.h"

class				MusicSFML : public IMusic
{
	sf::Music		music;
public:
	MusicSFML(void);
	~MusicSFML(void);
	virtual	bool	init(const std::string& name);
	virtual void	play();
	virtual void	pause();
	virtual void	stop();
	virtual void	setVolume(float _volume);
};

