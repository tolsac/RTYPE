/* Header global du Client.cpp. */
/* Auteur: Erick Clarivet */
/* Commencé le 06/01/13. */
/* Dernière modification: 06/01/13. */

#include		"Client.h"
#include		"Authentificate.hpp"

std::string Client::login = Client::getLogin();
std::string Client::roomName = "";

Client::Client(void)
{
}

Client::~Client(void)
{
}

bool				Client::init()
{
	Authentificate		auth;
	sf::RenderWindow	*window;

	auth.load();
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "Rtype");
	//window->SetActive(false);
	this->_tPool = new ThreadPool;
	this->_graphic = new Graphics;
	this->_aManager = new ActionManager;
	this->_nManager->getInstance();
	this->_nManager->getInstance()->setActionManager(this->_aManager);
	this->_graphic->setWindow(window);
	this->_graphic->init();
	this->_aManager->setSM(this->_graphic->getScreenManager());
	if (this->_nManager->getInstance()->init(auth.getIp(), auth.getPort()))
	  {
	    std::cout << "Success" << std::endl;
	    return true;
	  }
	std::cout << "Echec" << std::endl;
	return false;
}

void				Client::run()
{
	this->_nManager->getInstance()->sendPacket(PacketFactory::createPacketAuthentification(const_cast<char*>(Client::login.c_str())), true);
	this->_tPool->runTask(this->_nManager->getInstance());
	//this->_tPool->runTask(this->_graphic);
	this->_graphic->operator()();
	getchar();
}

std::string			Client::getLogin()
{
	Authentificate		a;

	a.load();
	return a.getLogin();
}
