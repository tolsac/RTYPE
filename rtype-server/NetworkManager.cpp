/*
** NetworkManager.cpp for NetworkManager in /home/tolsa/Documents/R-type/Network/libsocket/only_srv
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Mon Dec 24 07:45:46 2012 tolsa_c
** Last update Fri Jan 18 14:51:01 2013 tolsa_c
*/

#include "Logger.h"
#include "Convert.hh"
#include	"UdpSocket.h"
#include <NetworkManager.h>

NetworkManager::NetworkManager()
{
	this->_udpSocket = new UdpSocket();
}

NetworkManager::~NetworkManager()
{
}

void			NetworkManager::init()
{
	this->_tcpServer.setPacketList(&(this->_lstPackets));
	this->_tcpServer.setConnexionList(&(this->_lstConnexions));
	this->_tcpServer.start(4243, 100);
	this->_tcpServer.UdpListener(this->_udpSocket);
}

void			NetworkManager::run()
{

  //run TASK tcpserver
  while (1)
    {
      this->_tcpServer.run();
      //sleep(1);
    }
}

void			NetworkManager::operator()()
{
	while (1)
	{
		this->_tcpServer.run();
	}
}

int				NetworkManager::getPacketAvailableCount()
{
	int			size;

	size = -1;
	//if (takePacketList())
	//{
	size = this->_lstPackets.size();
	//	releasePacketList();
	//}
	return (size);
}

PacketInfo*		NetworkManager::readPacket()
{
	PacketInfo		*ptr = NULL;

	if (this->takePacketList())
	{
		//		Logger::logInfo("Liste des paquets prise.");
		//	std::cout << "Taille de la liste: " << this->getPacketList().size() << std::endl;
		if (this->getPacketList().size() > 0)
		{
			ptr = this->_lstPackets.back();
			this->_lstPackets.pop_back();
		}
		this->releasePacketList();
		//	Logger::logInfo("Liste de paquets relachee.");
	}
	return (ptr);
}

void			NetworkManager::sendPacket(PacketContainer::PacketSerialised *p, Connexion *c, bool TCP)
{
	if (TCP)
	{
		this->_tcpServer.sendPacketTcp(p, c);
		Logger::logInfo("sending on tcp : " + epi::toString(p->header.commandId));
	}
		
	else
	{
		this->_tcpServer.sendPacketUdp(p, c);
		Logger::logInfo("sending on udp : " + epi::toString(p->header.commandId));
	}
}

bool			NetworkManager::takeConnexionList()
{
	return (this->mConnexion.lock());
}

bool			NetworkManager::releaseConnexionList()
{
	return (this->mConnexion.unlock());
}

std::list<Connexion*>&	NetworkManager::getConnexionList()
{
	return (this->_lstConnexions);
}

bool			NetworkManager::takePacketList()
{
	return (this->mPacket.lock());
}

bool			NetworkManager::releasePacketList()
{
	return (this->mPacket.unlock());
}

std::list<PacketInfo*>&	NetworkManager::getPacketList()
{
	return (this->_lstPackets);
}

Connexion		*NetworkManager::getConnexionByNetInfos(std::string const& ip, int port)
{
	std::list<Connexion*>::iterator	it;
	Connexion				*ret;

	ret = NULL;
	//if (this->takeConnexionList())
	//{
	for (it = this->_lstConnexions.begin(); it != this->_lstConnexions.end(); ++it)
	{
		if ((*it)->getIp() == ip && (*it)->getPort() == port)
		{
			ret = (*it);
		}
	}
	//	this->releaseConnexionList();
	//}
	return (ret);
}

Connexion		*NetworkManager::getConnexionByLogin(std::string const& login)
{
	std::list<Connexion*>::iterator	it;
	Connexion				*ret;

	ret = NULL;
	//if (this->takeConnexionList())
	//{
	for (it = this->_lstConnexions.begin(); it != this->_lstConnexions.end(); ++it)
	{
		if ((*it)->getLogin() == login)
		{
			ret = (*it);
		}
	}
	//	this->releaseConnexionList();
	//}
	return (ret);
}

void			NetworkManager::update()
{
	//sort packet by timestamp :)
}
