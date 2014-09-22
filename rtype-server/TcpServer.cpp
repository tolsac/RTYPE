/*
** TcpServer.cpp for TcpServer in /home/tolsa/rtype-2015-tolsa_c/rtype-server
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 22:24:57 2013 tolsa_c
** Last update Thu Jan 10 01:32:36 2013 tolsa_c
*/

#include <TcpServer.h>

TcpServer::TcpServer()
{
#ifdef PLATFORM_LINUX
  this->_atcpServer = new TcpServerUnix();
#endif
#ifdef PLATFORM_WIN32
  this->_atcpServer = new TcpServerWin();
#endif
}

TcpServer::TcpServer(std::list<Connexion*>* clist, std::list<PacketInfo*>* plist)
{
#ifdef PLATFORM_LINUX
  this->_atcpServer = new TcpServerUnix(clist, plist);
#endif
#ifdef PLATFORM_WIN32
  this->_atcpServer = new TcpServerWin(clist, plist);
#endif
}

TcpServer::~TcpServer()
{}

bool				TcpServer::start()
{
  return (this->_atcpServer->start());
}

bool				TcpServer::start(int port, int listen)
{
  return (this->_atcpServer->start(port, listen));
}

bool				TcpServer::UdpListener(UdpSocket *us)
{
  return (this->_atcpServer->UdpListener(us));
}

void				TcpServer::setPacketList(std::list<PacketInfo*> *plist)
{
  this->_atcpServer->setPacketList(plist);
}

void				TcpServer::setConnexionList(std::list<Connexion*> *clist)
{
  this->_atcpServer->setConnexionList(clist);
}

bool				TcpServer::bindSocket(int port)
{
  return (this->_atcpServer->bindSocket(port));
}

bool				TcpServer::listenSocket(int listen)
{
  return (this->_atcpServer->listenSocket(listen));
}

void				TcpServer::acceptSocket()
{
  this->_atcpServer->acceptSocket();
}

std::list<Connexion*>::iterator& TcpServer::readPacketTcp(std::list<Connexion*>::iterator& it)
{
  return (this->_atcpServer->readPacketTcp(it));
}

void				TcpServer::readPacketUdp()
{
  this->_atcpServer->readPacketUdp();
}

void				TcpServer::sendPacketTcp(PacketContainer::PacketSerialised* p, Connexion *c)
{
  this->_atcpServer->sendPacketTcp(p, c);
}

void				TcpServer::sendPacketUdp(PacketContainer::PacketSerialised* p, Connexion *c)
{
  this->_atcpServer->sendPacketUdp(p, c);
}

void				TcpServer::run()
{
  this->_atcpServer->run();
}
