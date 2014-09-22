#pragma once

#include			<SFML/Audio.hpp>

class				IMusic
{
public:
	virtual ~IMusic(void) {}
	virtual	bool	init(const std::string& name) = 0;
	virtual void	play() = 0;
	virtual void	pause() = 0;
	virtual void	stop() = 0;
	virtual void	setVolume(float _volume) = 0;
};

