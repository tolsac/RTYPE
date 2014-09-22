#include "Game.h"
#include <Singleton.hpp>
#include <NetworkManager.h>
#include <PacketFactory.h>

Game::Game()
{

}

Game::~Game()
{

}

bool	Game::LoadRessources()
{
	if (!this->file.LoadContent("assets.cme", this->attributes, this->contents))
		return (false);
	for (int i = 0; i < (int)this->attributes.size(); i++)
	{
		for (int j = 0; j < (int)this->attributes[i].size(); j++)
		{
			std::string att = this->attributes[i][j];
			if (att == "Image")
			{
				sf::Image *tmp = new sf::Image();
				if (!tmp->LoadFromFile(this->contents[i][j]))
				{
					std::cout << "Failed from loading " << this->contents[i][j] << std::endl;
					return (false);
				}
				else
				{
					int id;
					if (this->contents[i][j].find_last_of("/") == -1)
					{
						std::string str;

						str = this->contents[i][j].substr(0, this->contents[i][j].find("."));
						id = atoi(str.c_str());
					}
					else
					{
						id = atoi(this->contents[i][j].substr(this->contents[i][j].find_last_of("/") + 1, (this->contents[i][j].find_last_of("/") + 1 - this->contents[i][j].find("."))).c_str());
					}
					tmp->CreateMaskFromColor(sf::Color(255, 0, 255));
					this->myRessources[id] = tmp;
					std::cout << "added ressource " << id << ", " << tmp << std::endl;
				}

			}
			if (att == "Menu")
			{
				std::cout << att << " AND " << this->contents[i][j] << std::endl;
			}
		}
	}
	return (true);
}

bool	Game::LoadRessources(SoundManager& soundmanager)
{
	if (!this->file.LoadContent("assets.cme", this->attributes, this->contents))
		return (false);
	for (int i = 0; i < (int)this->attributes.size(); i++)
	{
		for (int j = 0; j < (int)this->attributes[i].size(); j++)
		{
			std::string att = this->attributes[i][j];
			if (att == "Image")
			{
				sf::Image *tmp = new sf::Image();
				if (!tmp->LoadFromFile(this->contents[i][j]))
				{
					std::cout << "Failed from loading " << this->contents[i][j] << std::endl;
					return (false);
				}
				else
				{
					int id;
					if (this->contents[i][j].find_last_of("/") == -1)
					{
						std::string str;

						str = this->contents[i][j].substr(0, this->contents[i][j].find("."));
						id = atoi(str.c_str());
					}
					else
					{
						id = atoi(this->contents[i][j].substr(this->contents[i][j].find_last_of("/") + 1, (this->contents[i][j].find_last_of("/") + 1 - this->contents[i][j].find("."))).c_str());
					}
					tmp->CreateMaskFromColor(sf::Color(255, 0, 255));
					this->myRessources[id] = tmp;
				}

			}
			if (att == "Sound")
			{
				sf::SoundBuffer	*buffer = new sf::SoundBuffer();

				if (!buffer->LoadFromFile(this->contents[i][j]))
				{
					std::cout << "Failed from loading " << this->contents[i][j] << std::endl;
					return (false);
				}
				else
				{
					int id;
					if (this->contents[i][j].find_last_of("/") == -1)
					{
						std::string str;

						str = this->contents[i][j].substr(0, this->contents[i][j].find("."));
						id = atoi(str.c_str());
					}
					else
					{
						id = atoi(this->contents[i][j].substr(this->contents[i][j].find_last_of("/") + 1, (this->contents[i][j].find_last_of("/") + 1 - this->contents[i][j].find("."))).c_str());
					}
					soundmanager.addSound(id, *buffer);
					this->mySounds[id] = buffer;
				}
			}
			if (att == "Music")
			{
				IMusic		*tmp = new MusicSFML();

				if (!tmp->init(this->contents[i][j]))
				{
					std::cout << "Failed from loading " << this->contents[i][j] << std::endl;
					return (false);
				}
				else
				{
					int id;
					if (this->contents[i][j].find_last_of("/") == -1)
					{
						std::string str;

						str = this->contents[i][j].substr(0, this->contents[i][j].find("."));
						id = atoi(str.c_str());
					}
					else
					{
						id = atoi(this->contents[i][j].substr(this->contents[i][j].find_last_of("/") + 1, (this->contents[i][j].find_last_of("/") + 1 - this->contents[i][j].find("."))).c_str());
					}
					soundmanager.addMusic(id, tmp);
				}

			}
		}
	}
	return (true);
}

void Game::init()
{
	this->LoadRessources();
	//this->myEntities.addEntity(1520, 1, 0.0f, 0.0f, this->myRessources[3]);
	//this->myEntities.addEntity(1520, 2, 0.0f, 0.0f, this->myRessources[2]);
}

void Game::init(SoundManager& soundmanager)
{
	this->LoadRessources(soundmanager);
	//this->myEntities.addEntity(1520, 1, 0.0f, 0.0f, this->myRessources[3]);
	//this->myEntities.addEntity(1520, 2, 0.0f, 0.0f, this->myRessources[2]);
}

void Game::Draw(sf::RenderWindow *Window)
{
	//std::cout << "Game draw" << std::endl;
	int j = 0;
	std::map<int, Entity *> ent = this->myEntities.getEntities();
	std::map<int, Entity *>::iterator iter;
	for (iter = ent.begin(); iter != ent.end(); ++iter)
	{
		(iter->second)->updatePosition(Window->GetFrameTime());
		(iter->second)->updateAnim(Window->GetFrameTime());
		Window->Draw(iter->second->getSprite());
		j++;
	}
}

void Game::Clear()
{
	std::cout << "Je clear ressources GAME" << std::endl;
	this->myEntities.getEntities().clear();
	std::cout << this->myEntities.getEntities().size() << std::endl;
}

EntityManager &				Game::getEntityManager()
{
	return this->myEntities;
}

std::map<int, sf::Image *> &	Game::getRessources()
{
	return this->myRessources;
}

void	     Game::updateEvent(sf::Event &e)
{
  Singleton<NetworkManager>	*sNm = NULL;

  if (e.Type == sf::Event::KeyPressed)
    if (e.Key.Code == sf::Key::Up) 
      {
	//	std::cout << "UP" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_UP), false);
      }
    else if (e.Key.Code == sf::Key::Down)
      {
	//std::cout << "DOWN" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_DOWN), false);
      }
    else if (e.Key.Code == sf::Key::Left)
      {
	//std::cout << "LEFT" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_LEFT), false);
      } 
    else if (e.Key.Code == sf::Key::Right)
      {
	//std::cout << "RIGHT" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_RIGHT), false);
      }
    else if (e.Key.Code == sf::Key::Space)
      {
	//std::cout << "SPACE" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketShooting(Protocol::SHOOT), false);
      }
}

void	     Game::updateEvent(sf::Event &e, SoundManager&s)
{
  Singleton<NetworkManager>	*sNm = NULL;

  if (e.Type == sf::Event::KeyPressed)
    if (e.Key.Code == sf::Key::Up) 
      {
	//	std::cout << "UP" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_UP), false);
      }
    else if (e.Key.Code == sf::Key::Down)
      {
	//std::cout << "DOWN" << std::endl;
 		  sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_DOWN), false);
      }
    else if (e.Key.Code == sf::Key::Left)
      {
	//std::cout << "LEFT" << std::endl;
 		  sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_LEFT), false);
      } 
    else if (e.Key.Code == sf::Key::Right)
      {
	//std::cout << "RIGHT" << std::endl;
		  sNm->getInstance()->sendPacket(PacketFactory::createPacketMovement(Protocol::MOVE_RIGHT), false);
      }
    else if (e.Key.Code == sf::Key::Space)
      {
  	    s.playSoundById(SoundManager::FIRE);
	//std::cout << "SPACE" << std::endl;
	sNm->getInstance()->sendPacket(PacketFactory::createPacketShooting(Protocol::SHOOT), false);
      }
}
