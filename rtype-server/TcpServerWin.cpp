/*
** TcpServer.cpp for TcpServer in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:55:18 2012 tolsa_c
** Last update Sat Jan 12 18:00:48 2013 tolsa_c
*/

#include <stdio.h>
#include <stdlib.h>
#include <TcpServer.h>
#include <TcpSocket.h>
#include <Singleton.hpp>
#include <NetworkManager.h>

#include	"Logger.h"
#include	"Convert.hh"

void hexdump (char *desc, char *addr, int len);

/*
void debugPacket(PacketInfo *pInfo)
{
printf("magic %d\ncheckcum %d\ntimestamp %d\ncommandId %hd\ndataSize %hd\n",
pInfo->packet->header.magic,
pInfo->packet->header.checksum,
pInfo->packet->header.timestamp,
pInfo->packet->header.commandId,
pInfo->packet->header.dataSize);
}
*/

TcpServerWin::TcpServerWin(std::list<Connexion*> *c, std::list<PacketInfo*> *p)
{
	this->_lstConnexions = c;
	this->_lstPackets = p;
}

TcpServerWin::TcpServerWin()
{
}

TcpServerWin::~TcpServerWin()
{
	WSACleanup();
}

bool				TcpServerWin::start()
{
	this->_tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_tcpSocket <= 0)
		return (false);
	return (true);
}

bool				TcpServerWin::start(int port, int listen)
{
	WSADATA			wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);
	this->_tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_tcpSocket <= 0)
		return (false);
	std::cout << "bind(127.0.0.1, " << port << ");" << std::endl;
	if (this->bindSocket(port) == false)
		return (false);
	if (this->listenSocket(listen) == false)
		return (false);
	return (true);
}

bool				TcpServerWin::UdpListener(UdpSocket *s)
{
	this->_udpSocket = s;
	//this->_udpSocket = new UdpSocket;
	return (this->_udpSocket->bindSocket(4244));
}

void				TcpServerWin::setPacketList(std::list<PacketInfo*> *plist)
{
	this->_lstPackets = plist;
}

void				TcpServerWin::setConnexionList(std::list<Connexion*> *clist)
{
	this->_lstConnexions = clist;
}

bool				TcpServerWin::bindSocket(int port)
{
	struct sockaddr_in		my_addr;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY; 
	if (bind(this->_tcpSocket, (struct sockaddr*)(&my_addr), sizeof(struct sockaddr)) < 0)
		return (false);
	return (true);
}

bool				TcpServerWin::listenSocket(int max)
{
	if (listen(this->_tcpSocket, max) < 0)
		return (false);
	return (true);
}

void							TcpServerWin::acceptSocket()
{
	int							newFd;
	struct sockaddr_in			newIp;
	socklen_t					size;
	TcpSocket					*clt;
	Connexion					*con;
	Singleton<NetworkManager>	*sNm = NULL;

	size = sizeof(struct sockaddr);
	newFd = accept(this->_tcpSocket, (struct sockaddr*)&newIp, &size);
	clt = new TcpSocket(newFd);
	con = new Connexion;
	con->setSocket(clt);
	con->setIp(inet_ntoa(newIp.sin_addr));
	con->setPort(ntohs((int)(newIp.sin_port)));
	if (sNm->getInstance()->takeConnexionList())
	{
		this->_lstConnexions->push_front(con);
		sNm->getInstance()->releaseConnexionList();
	}
	else
	{
		/*
		Throw something ?
		*/
	}
	std::cout << "[Server] new connexion :: [" << newFd << "]" << std::endl;
}

void								TcpServerWin::run()
{
	fd_set							fread;
	unsigned int					highest;
	std::list<Connexion*>::iterator	it;
	Singleton<NetworkManager>		*sNm = NULL;
	struct timeval					t;

	t.tv_sec = 0;
	t.tv_usec = 20000;
	highest = (((unsigned int) this->_tcpSocket > this->_udpSocket->getSocket()) 
		? (this->_tcpSocket) 
		: (this->_udpSocket->getSocket()));
	FD_ZERO(&fread);
	FD_SET(this->_tcpSocket, &fread);
	FD_SET(this->_udpSocket->getSocket(), &fread);
	if (sNm->getInstance()->takeConnexionList())
	{
		for (it = this->_lstConnexions->begin() ; it != this->_lstConnexions->end() ; ++it)
		{
			FD_SET((*it)->getSocket()->getSocket(), &fread);
			if ((*it)->getSocket()->getSocket() > highest)
				highest = (*it)->getSocket()->getSocket();
		}
		sNm->getInstance()->releaseConnexionList();
	}
	if (select(highest + 1, &fread, NULL, NULL, NULL) == -1)
		return;
	if (FD_ISSET(this->_tcpSocket, &fread))
		this->acceptSocket();
	if (FD_ISSET(this->_udpSocket->getSocket(), &fread))
		this->readPacketUdp();
	if (sNm->getInstance()->takeConnexionList())
	{
		for (it = this->_lstConnexions->begin() ; it != this->_lstConnexions->end() ; ++it)
		{
			if (FD_ISSET((*it)->getSocket()->getSocket(), &fread))
				it = this->readPacketTcp(it);
			if (it == this->_lstConnexions->end())
			{
				break;
			}
		}
		sNm->getInstance()->releaseConnexionList();
	}
}

void							TcpServerWin::readPacketUdp()
{
	struct sockaddr_in			from;
	char						*buff;
	int							bav = 65535;
	Singleton<NetworkManager>	*sNm = NULL;
	Connexion					*con;
	PacketInfo					*pInfo;
	PacketContainer::Header		hdr;

	buff = new char[bav];
	memset(buff, 0, bav);
	bav = this->_udpSocket->readDatagram(buff, bav, &from);
	this->_buffers[from.sin_port].append(buff, bav);
	while (this->_buffers[from.sin_port].size() >= sizeof(PacketContainer::Header))
	{
		pInfo = new PacketInfo;
		pInfo->packet = new PacketContainer;
		pInfo->packet->deserialize_header(this->_buffers[from.sin_port].get(sizeof(PacketContainer::Header)), hdr);
		if (this->_buffers[from.sin_port].size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
		{
			delete pInfo->packet;
			pInfo->packet = new PacketContainer(this->_buffers[from.sin_port].extract(sizeof(PacketContainer::Header) + hdr.dataSize));
		}
		else
			return;
		if (pInfo->packet->isValid())
		{
			std::cout << "Udp -> [" << pInfo->packet->getCommandID() << "]" << std::endl;
			if (sNm->getInstance()->takePacketList())
			{
				con = new Connexion;
				con->setIp(inet_ntoa(from.sin_addr));
				con->setPort(from.sin_port);
				pInfo->connexion = con;
				this->_lstPackets->push_back(pInfo);
				sNm->getInstance()->releasePacketList();
			}	
		}
	}
}

std::list<Connexion*>::iterator&	TcpServerWin::readPacketTcp(std::list<Connexion*>::iterator &clt)
{
	TcpSocket						*socket;
	int								bav;
	PacketInfo						*pInfo;
	char							*buff;
	PacketContainer::Header			hdr;
	Singleton<NetworkManager>		*sNm = NULL;

	socket = (*clt)->getSocket();
	bav = socket->bytesAvailable();
	if (bav < 0)
	{
		socket->closeSocket();
		clt = this->_lstConnexions->erase(clt);
		std::cout << "[Server] deconnexion :: [" << socket->getSocket() << "]" << std::endl;
	}
	else
	{
		buff = new char[bav];
		socket->read(buff, bav);
		(*clt)->getTcpBuffer().append(buff, bav);
		while ((*clt)->getTcpBuffer().size() >= sizeof(PacketContainer::Header))
		{
			pInfo = new PacketInfo;
			pInfo->packet = new PacketContainer;
			pInfo->packet->deserialize_header((*clt)->getTcpBuffer().get(sizeof(PacketContainer::Header)), hdr);
			std::cout << "buffer size = " << (*clt)->getTcpBuffer().size() << " >= taille packet" << sizeof(PacketContainer::Header) + hdr.dataSize<<std::endl;
			if ((*clt)->getTcpBuffer().size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
			{
				delete pInfo->packet;
				pInfo->packet = new PacketContainer((*clt)->getTcpBuffer().extract(sizeof(PacketContainer::Header) + hdr.dataSize));
			}
			else
			{
				return (clt);
			}
			if (pInfo->packet->isValid())
			{
				if (sNm->getInstance()->takePacketList())
				{
					pInfo->connexion = (*clt);
					this->_lstPackets->push_back(pInfo);
					sNm->getInstance()->releasePacketList();
				}
			}
		}
	}
	return (clt);
}

void				TcpServerWin::sendPacketTcp(PacketContainer::PacketSerialised *p, Connexion *c)
{
	Singleton<NetworkManager>	*sNm = NULL;

	if (sNm->getInstance()->takeConnexionList())
	{
		c->getSocket()->writePacket(p);
		sNm->getInstance()->releaseConnexionList();
	}
}

void				TcpServerWin::sendPacketUdp(PacketContainer::PacketSerialised *p, Connexion *c)
{
	Singleton<NetworkManager>	*sNm = NULL;

	if (sNm->getInstance()->takeConnexionList())
	{
		std::cout << " ip : " << c->getIp() << " port : " << c->getPort() <<std::endl;
		this->_udpSocket->writePacket(p, c->getIp(), 4245);
		sNm->getInstance()->releaseConnexionList();
	}
}

