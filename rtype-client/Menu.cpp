#include "Menu.h"
#include "Client.h"

Menu::Menu(int *state)
{
	this->bManager = new ButtonManager;
	this->SMState = state;
}

Menu::~Menu()
{

}

void Menu::init()
{
	/*
	Singleton<NetworkManager> *sNm;  
	sNm->getInstance()->sendPacket(PacketFactory::createPacketListRoom(), true)
	*/

	this->bManager->addButton("Quit", Button::EXIT);
	this->bManager->addButton("Room list", Button::ENTER_ROOM_LIST);  
	this->bManager->addButton("Create room", Button::CREATE_ROOM);
}

void Menu::Draw(sf::RenderWindow *Window)
{
	this->bManager->Draw(Window);
}

void Menu::Clear()
{
	std::cout << "Je clear ressources menu" << std::endl;
	this->bManager->clearButtons();	
}


void			Menu::updateEvent(sf::Event &e)
{
	//si entree
	Singleton<NetworkManager>		*sNm = NULL;
	PacketContainer			*packet;
	std::string				s;

	if (e.Key.Code == sf::Key::Return && e.Type == sf::Event::KeyPressed)
	{
		std::cout << "current focus : " << this->bManager->getFocus() << std::endl;
		if (this->bManager->getFocusedButton()->getAction() == Button::CREATE_ROOM)
		{
			s = "Room of ";
			s += Client::login;
			packet = PacketFactory::createPacketCreateRoom(const_cast<char*>(s.c_str()), 4, 0, 0);
			std::cout << "create room" << std::endl;
			sNm->getInstance()->sendPacket(packet, true);
			Client::roomName = s;
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_ROOM_LIST)
		{
			packet = PacketFactory::createPacketShowRoom();
			std::cout << "enter room list" << std::endl;
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_ROOM)
		{
			packet = PacketFactory::createPacketJoinRoom(this->bManager->getFocusedButton()->getTextButton());
			Client::roomName = this->bManager->getFocusedButton()->getTextButton();
			std::cout << "enter join room" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::EXIT)
		{
			std::cout << "exit game" << std::endl;
			exit(0);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::RETURN)
		{
			//if IN_ROOM send packet leave room
			std::cout << "return" << std::endl;
			this->bManager->clearButtons();
			*(this->SMState) = 0;
			this->init();
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::LEAVE_ROOM)
		{
			packet = PacketFactory::createPacketLeaveRoom();
			std::cout << "enter leave room" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_GAME)
		{
			std::string s;
			s = "Room of ";
			s += Client::login;
			packet = PacketFactory::createPacketLaunchGame(s);
			std::cout << "enter launch game" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
			*(this->SMState) = 3;
		}
	}
	//sinon
	if (e.Type == sf::Event::KeyPressed) 
		this->bManager->updateFocus(e);
}

void			Menu::updateEvent(sf::Event &e, SoundManager& soundmanager)
{
	//si entree
	Singleton<NetworkManager>		*sNm = NULL;
	PacketContainer			*packet;
	std::string				s;

	if (e.Key.Code == sf::Key::Return && e.Type == sf::Event::KeyPressed)
	{
		std::cout << "current focus : " << this->bManager->getFocus() << std::endl;
		if (this->bManager->getFocusedButton()->getAction() == Button::CREATE_ROOM)
		{
	    soundmanager.playSoundById(SoundManager::BIP);
			s = "Room of ";
			s += Client::login;
			packet = PacketFactory::createPacketCreateRoom(const_cast<char*>(s.c_str()), 4, 0, 0);
			std::cout << "create room" << std::endl;
			sNm->getInstance()->sendPacket(packet, true);
			Client::roomName = s;
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_ROOM_LIST)
		{
				    soundmanager.playSoundById(SoundManager::BIP);

			packet = PacketFactory::createPacketShowRoom();
			std::cout << "enter room list" << std::endl;
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_ROOM)
		{
		    soundmanager.playSoundById(SoundManager::BIP);

			packet = PacketFactory::createPacketJoinRoom(this->bManager->getFocusedButton()->getTextButton());
			Client::roomName = this->bManager->getFocusedButton()->getTextButton();
			std::cout << "enter join room" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::EXIT)
		{
	    soundmanager.playSoundById(SoundManager::BIP);
			std::cout << "exit game" << std::endl;
			exit(0);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::RETURN)
		{
				    soundmanager.playSoundById(SoundManager::BIP);

			//if IN_ROOM send packet leave room
			std::cout << "return" << std::endl;
			this->bManager->clearButtons();
			*(this->SMState) = 0;
			this->init();
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::LEAVE_ROOM)
		{
	    soundmanager.playSoundById(SoundManager::BIP);
			packet = PacketFactory::createPacketLeaveRoom();
			std::cout << "enter leave room" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
		}
		else if (this->bManager->getFocusedButton()->getAction() == Button::ENTER_GAME)
		{
				    soundmanager.playSoundById(SoundManager::BIP);

			std::string s;
			s = "Room of ";
			s += Client::login;
			packet = PacketFactory::createPacketLaunchGame(s);
			std::cout << "enter launch game" << std::endl;
			packet->displayPacket();
			sNm->getInstance()->sendPacket(packet, true);
			*(this->SMState) = 3;
		}
	}
	//sinon
	if (e.Type == sf::Event::KeyPressed) 
	{
		this->bManager->updateFocus(e);
	    soundmanager.playSoundById(SoundManager::BIP);
	}
}

ButtonManager		*Menu::getButtonManager()
{
	return (this->bManager);
}
