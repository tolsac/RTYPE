#include "SoundManager.h"


SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}

void			SoundManager::addSound(int id, const sf::SoundBuffer& buffer)
{
	ISound		*tmp = new SoundSFML();
	eAction		e = (eAction)id;
	tmp->init(buffer);
	this->sounds[e] = tmp;
}

void			SoundManager::addMusic(int id, IMusic* tmp)
{
	this->musics[id] = tmp;
}

void			SoundManager::playSoundById(SoundManager::eAction id)
{
	if (this->sounds.find(id) != this->sounds.end())
	{
		(*this->sounds[id]).play();
		return;
	}
	std::cout << "Cannot find sound." << std::endl;
}

void			SoundManager::playMusicById(int id)
{
	if (this->musics.find(id) != this->musics.end())
	{
		(*this->musics[id]).play();
		return;
	}
	std::cout << "Cannot find music." << std::endl;
}

void			SoundManager::pauseSoundById(SoundManager::eAction id)
{
	if (this->sounds.find(id) != this->sounds.end())
	{
		(*this->sounds[id]).pause();
		return;
	}
	std::cout << "Cannot find sound." << std::endl;
}

void			SoundManager::pauseMusicById(int id)
{
	if (this->musics.find(id) != this->musics.end())
	{
		(*this->musics[id]).pause();
		return;
	}
	std::cout << "Cannot find music." << std::endl;
}

void			SoundManager::pauseSoundAll()
{
	for (std::map<SoundManager::eAction, ISound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it)
		(*it).second->pause();
}

void			SoundManager::pauseMusicAll()
{
	for (std::map<int, IMusic*>::iterator it = this->musics.begin(); it != this->musics.end(); ++it)
		(*it).second->pause();
}
	
void			SoundManager::stopSoundById(SoundManager::eAction id)
{	
	if (this->sounds.find(id) != this->sounds.end())
	{
		(*this->sounds[id]).stop();
		return;
	}
	std::cout << "Cannot find sound." << std::endl;
}

	
void			SoundManager::stopMusicById(int id)
{
	if (this->musics.find(id) != this->musics.end())
	{
		(*this->musics[id]).stop();
		return;
	}
	std::cout << "Cannot find music." << std::endl;
}
	
void			SoundManager::stopSoundAll()
{
	for (std::map<SoundManager::eAction, ISound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it)
		(*it).second->stop();
}
	
void			SoundManager::stopMusicAll()
{
	for (std::map<int, IMusic*>::iterator it = this->musics.begin(); it != this->musics.end(); ++it)
		(*it).second->stop();
}
	
void			SoundManager::setVolumeSoundById(SoundManager::eAction id, float _volume)
{
	if (this->sounds.find(id) != this->sounds.end())
	{
		(*this->sounds[id]).setVolume(_volume);
		return;
	}
	std::cout << "Cannot find music." << std::endl;
}

void			SoundManager::setVolumeMusicById(int id, float _volume)
{
	if (this->musics.find(id) != this->musics.end())
	{
		(*this->musics[id]).setVolume(_volume);
		return;
	}
	std::cout << "Cannot find music." << std::endl;
}