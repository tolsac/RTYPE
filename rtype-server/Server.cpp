/*
** Server.cpp for  in /home/tolsa/rtype-2015-tolsa_c/rtype-server
** 
** Made by tolsa_c
** Login   <tolsa@epitech.net>
** 
** Started on  Wed Jan  9 12:41:32 2013 tolsa_c
** Last update Sat Jan 19 14:31:58 2013 tolsa_c
*/

#include <Server.h>
#include <Platform.h>

Server::Server()
{
	Logger::logInfo("Construction du serveur.");
	this->_nManager->getInstance();
	/*this->_rManager = new RoomManager;*/
	this->_tPool = new ThreadPool;
	this->_aManager = new ActionManager();
}


Server::~Server()
{
	/*delete this->_rManager;*/
	delete this->_tPool;
	this->_nManager->killInstance();
	delete (this->_aManager);
	Logger::logInfo("Destruction du serveur.");
}

void		Server::init()
{
	this->_nManager->getInstance()->init();
}

void		Server::run()
{
	//On lance le networkManager dans un Thread
	this->_tPool->addTask(this->_nManager->getInstance());
	this->_tPool->addTask(this->_aManager);
	this->_tPool->runTask();
	//this->_tPool->runTask(this->_nManager->getInstance());
	//this->_tPool->runTask(this->_aManager);
	//this->_aManager->operator()();

	getchar();
	this->_tPool->joinAll();
}
