#pragma once

#include	<iostream>
#include	<map>
#include	"SoundSFML.h"
#include	"MusicSFML.h"

class		SoundManager
{
public:
	enum	eAction
	{
		FIRE,
		EXPLOSION,
		WIN,
		LOOSE,
		INFO,
		BIP
	};
	private:
	std::map<eAction, ISound*>	sounds;
	std::map<int, IMusic*>	musics;
public:
	SoundManager(void);
	~SoundManager(void);

	bool	initSound(const std::string& name);
	void	addSound(int id, const sf::SoundBuffer& buffer);
	void	addMusic(int id, IMusic* tmp);
	bool	initMusic();
	void	playSoundById(eAction id);
	void	playMusicById(int id);
	void	pauseSoundById(eAction id);
	void	pauseMusicById(int id);
	void	pauseSoundAll();
	void	pauseMusicAll();
	void	stopSoundById(eAction id);
	void	stopMusicById(int id);
	void	stopSoundAll();
	void	stopMusicAll();
	void	setVolumeSoundById(eAction id, float _volume);
	void	setVolumeMusicById(int id, float _volume);
};

