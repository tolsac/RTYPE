/* Header global du NetworkManager.cpp. */
/* Auteur: Erick Clarivet */
/* Commencé le 06/01/13. */
/* Dernière modification: 06/01/13. */
#include <iostream>

#include					"NetworkManager.h"

#include	"Logger.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager(void)
{
}

void				NetworkManager::setActionManager(ActionManager *a)
{
	this->aManager = a;
}

bool				NetworkManager::init(const std::string& _ip, int _port)
{
	this->udpSocket = new UdpSocket;
	this->tcpSocket = new TcpSocket;
	this->udpSocket->bindSocket(4245);
	this->ip = _ip;
	this->port = _port;
	//if (!this->bindSocket(4242))
	//	return false;
	std::cout << "connect(" << _ip <<", "<<port<<");"<<std::endl;
	if (!this->tcpSocket->connectSocket(_ip, _port))
		return false;
	if (!this->tcpSocket->block())
		return false;
	return true;
}

bool				NetworkManager::bindSocket(int port)
{
	struct sockaddr_in		my_addr;

	my_addr.sin_family = AF_INET;       
	my_addr.sin_port = htons(port);  
	my_addr.sin_addr.s_addr = INADDR_ANY; 
	if (bind(this->tcpSocket->getSocket(), (struct sockaddr*)(&my_addr), sizeof(struct sockaddr)) < 0)
		return (false);
	return (true);
}

void				NetworkManager::update()
{
}

void				NetworkManager::operator()()
{
	while (1)
		this->run();
}

void				NetworkManager::run()
{
	fd_set			readFs;
	int			    highest;

	highest = ((this->tcpSocket->getSocket() > this->udpSocket->getSocket()) 
		? (this->tcpSocket->getSocket()) 
		: (this->udpSocket->getSocket()));
	FD_ZERO(&readFs);
	FD_SET(this->udpSocket->getSocket() , &readFs);
	FD_SET(this->tcpSocket->getSocket(), &readFs);
	if (select(highest + 1, &readFs, NULL, NULL, NULL) == -1)
		return;
	if (FD_ISSET(this->tcpSocket->getSocket(), &readFs))
		this->readPacketTcp();
	if (FD_ISSET(this->udpSocket->getSocket(), &readFs))
		this->readPacketUdp();
}

void				NetworkManager::sendPacket(PacketContainer* p, bool TCP)
{
	if (TCP)
		this->sendPacketTcp(p);
	else
		this->sendPacketUdp(p);
}

std::list<PacketContainer*>&			NetworkManager::getPacketList()
{
	return this->packets;
}

void				NetworkManager::readPacketTcp()
{
  int						bav;
  PacketContainer			*p;
  PacketContainer::Header	hdr;
  char					*tmpbuffer;

  bav = this->tcpSocket->bytesAvailable();
  if (bav < 0)
    {
      std::cout << "bav = -1 in NetworkManager::readPacketTcp" << std::endl;
      //Logger::logInfo("bav = -1 in NetworkManager::readPacketTcp");
      return;
    }
  tmpbuffer = new char[bav];
  memset(tmpbuffer, 0, bav);
  this->tcpSocket->read(tmpbuffer, bav);
  this->bufferTcp.append(tmpbuffer, bav);
  while (this->bufferTcp.size() >= sizeof(PacketContainer::Header))
    {
      p = new PacketContainer;
      p->deserialize_header(this->bufferTcp.get(sizeof(PacketContainer::Header)), hdr);
      if (this->bufferTcp.size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
	{
	  delete p;
	  p = new PacketContainer(this->bufferTcp.extract(sizeof(PacketContainer::Header) + hdr.dataSize));
	}
      else
	return;
      if (p->isValid())
	this->aManager->doAction(p);
      else
	{
	  p->displayPacket();
	  delete p;
	  std::cout << "Wrong tcp packet" << std::endl;
	}
    }
}
void				NetworkManager::readPacketUdp()
{
  int				bav = 65535;
  PacketContainer		*p;
  PacketContainer::Header	hdr;
  char				*tmpbuffer;

  tmpbuffer = new char[bav];
  memset(tmpbuffer, 0, bav);
  bav = this->udpSocket->readDatagram(tmpbuffer, bav);
  this->bufferUdp.append(tmpbuffer, bav);
  while (this->bufferUdp.size() >= sizeof(PacketContainer::Header))
    {
      p = new PacketContainer;
      p->deserialize_header(this->bufferUdp.get(sizeof(PacketContainer::Header)), hdr);
      if (this->bufferUdp.size() >= sizeof(PacketContainer::Header) + hdr.dataSize)
	{
	  delete p;
	  p = new PacketContainer(this->bufferUdp.extract(sizeof(PacketContainer::Header) + hdr.dataSize));
	}
      else
	return;
      if (p->isValid())
	{
	  std::cout << "GOT UDP PACKET" << std::endl;
	  this->aManager->doAction(p);
	}		
      else
	{
	  delete p;
	  std::cout << "Wrong udp packet" << std::endl;
	}
    }
}

PacketContainer::PacketSerialised*	NetworkManager::getPacket()
{
	PacketContainer::PacketSerialised		*ptr = NULL;

	if (this->getPacketAvailableCount())
	{
		ptr = this->packets.front()->getPacketSerialised();
		this->packets.pop_front();
	}
	return (ptr);
}

void				NetworkManager::sendPacketTcp(PacketContainer* p)
{
	// check si il est valide
  std::cout << "tcp = " << this->tcpSocket->writePacket(p->getPacketSerialised()) << std::endl;
}

void				NetworkManager::sendPacketUdp(PacketContainer* p)
{
  std::cout << "udp = " << this->udpSocket->writePacket(p->getPacketSerialised(), this->ip, 4244) << std::endl;
}

int					NetworkManager::getPacketAvailableCount()
{
	return (this->packets.size());
}
