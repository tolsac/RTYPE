/*
** TcpServer.cpp for TcpServer in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:55:18 2012 tolsa_c
** Last update Sat Jan 19 22:15:01 2013 tolsa_c
*/

#include <stdio.h>
#include <stdlib.h>
#include <TcpServerUnix.h>
#include <TcpSocketUnix.h>
#include <Singleton.hpp>
#include <NetworkManager.h>

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

TcpServerUnix::TcpServerUnix(std::list<Connexion*> *c, std::list<PacketInfo*> *p)
{
  this->_lstConnexions = c;
  this->_lstPackets = p;
}

TcpServerUnix::TcpServerUnix()
{
}

TcpServerUnix::~TcpServerUnix()
{}

bool				TcpServerUnix::start()
{
  this->_tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_tcpSocket <= 0)
    return (false);
  return (true);
}

bool				TcpServerUnix::start(int port, int listen)
{
  this->_tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_tcpSocket <= 0)
    return (false);
  if (this->bindSocket(port) == false)
    return (false);
  if (this->listenSocket(listen) == false)
    return (false);
  return (true);
}

bool				TcpServerUnix::UdpListener(UdpSocket *s)
{
  this->_udpSocket = s;
  this->_udpSocket = new UdpSocket;
  return (this->_udpSocket->bindSocket(4244));
}

void				TcpServerUnix::setPacketList(std::list<PacketInfo*> *plist)
{
  this->_lstPackets = plist;
}

void				TcpServerUnix::setConnexionList(std::list<Connexion*> *clist)
{
  this->_lstConnexions = clist;
}

bool				TcpServerUnix::bindSocket(int port)
{
  struct sockaddr_in		my_addr;

  my_addr.sin_family = AF_INET;       
  my_addr.sin_port = htons(port);  
  my_addr.sin_addr.s_addr = INADDR_ANY; 
  if (bind(this->_tcpSocket, (struct sockaddr*)(&my_addr), sizeof(struct sockaddr)) < 0)
    return (false);
  return (true);
}

bool				TcpServerUnix::listenSocket(int max)
{
  if (listen(this->_tcpSocket, max) < 0)
    return (false);
  return (true);
}

void				TcpServerUnix::acceptSocket()
{
  int				newFd;
  struct sockaddr_in		newIp;
  socklen_t			size;
  TcpSocket			*clt;
  Connexion			*con;
  Singleton<NetworkManager>	*sNm;

  size = sizeof(struct sockaddr);
  newFd = accept(this->_tcpSocket, (struct sockaddr*)&newIp, &size);
  clt = new TcpSocket(newFd);
  con = new Connexion;
  con->setSocket(clt);
  con->setIp(inet_ntoa(newIp.sin_addr));
  con->setPort((int)(newIp.sin_port));
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

void				TcpServerUnix::run()
{
  fd_set				fread;
  int					highest;
  std::list<Connexion*>::iterator	it;
  Singleton<NetworkManager>		*sNm;
  struct timeval			t;

  t.tv_sec = 0;
  t.tv_usec = 20000;
  highest = ((this->_tcpSocket > this->_udpSocket->getSocket()) 
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
	if (FD_ISSET((*it)->getSocket()->getSocket(), &fread))
	  it = this->readPacketTcp(it);
      sNm->getInstance()->releaseConnexionList();
    }
}

void				 TcpServerUnix::readPacketUdp()
{
  struct sockaddr_in			from;
  char					*buff;
  int					bav;
  Singleton<NetworkManager>		*sNm;
  Connexion				*con;
  PacketInfo				*pInfo;
  PacketContainer::Header		hdr;

  bav = this->_udpSocket->bytesAvailable();
  buff = new char[bav];
  bzero(buff, bav);
  this->_udpSocket->readDatagram(buff, bav, &from);
  this->_buffers[from.sin_port].append(buff, bav);
  while (this->_buffers[from.sin_port].size() > sizeof(PacketContainer::Header))
    {
      pInfo = new PacketInfo;
      pInfo->packet = new PacketContainer;
      pInfo->packet->deserialize_header(this->_buffers[from.sin_port].get(sizeof(PacketContainer::Header)), hdr);
      if (this->_buffers[from.sin_port].size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
	{
	  delete pInfo->packet;
	  pInfo->packet = new PacketContainer(this->_buffers[from.sin_port].extract(sizeof(PacketContainer::Header) + hdr.dataSize));
	}
      if (pInfo->packet->isValid())
	{
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

std::list<Connexion*>::iterator& TcpServerUnix::readPacketTcp(std::list<Connexion*>::iterator &clt)
{
  TcpSocket			*socket;
  int				bav;
  PacketInfo			*pInfo;
  char				*buff;
  PacketContainer::Header	hdr;
  Singleton<NetworkManager>	*sNm;

  /**/
  //sleep(1);
  /**/

  socket = (*clt)->getSocket();
  bav = socket->bytesAvailable();
  if (bav == 0)
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
	  std::cout << (*clt)->getTcpBuffer().size()
		    << " >= "
		    << sizeof(PacketContainer::Header) + hdr.dataSize
		    << std::endl;
	  if ((*clt)->getTcpBuffer().size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
	    {
	      delete pInfo->packet;
	      pInfo->packet = new PacketContainer((*clt)->getTcpBuffer().extract(sizeof(PacketContainer::Header) + hdr.dataSize));
	    }
	  else
	    return (clt);
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

void				TcpServerUnix::sendPacketTcp(PacketContainer::PacketSerialised *p, Connexion *c)
{
  Singleton<NetworkManager>	*sNm;

  std::cout << "envoi tcp" << std::endl;
  if (sNm->getInstance()->takeConnexionList())
    {
      this->_udpSocket->writePacket(p, c->getIp(), 4245);
      c->getSocket()->writePacket(p);
      sNm->getInstance()->releaseConnexionList();
    }
}

void				TcpServerUnix::sendPacketUdp(PacketContainer::PacketSerialised *p, Connexion *c)
{
  Singleton<NetworkManager>	*sNm;

  std::cout << "envoi udp = " << c->getIp() << " : " << 4245 << std::endl;
  if (sNm->getInstance()->takeConnexionList())
    {
      this->_udpSocket->writePacket(p, c->getIp(), 4245);
      sNm->getInstance()->releaseConnexionList();
    }
}
