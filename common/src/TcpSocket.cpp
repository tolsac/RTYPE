/*
** TcpSocket.cpp for TcpSocket in /home/tolsa/Documents/R-type/newSock
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 05:10:35 2013 tolsa_c
** Last update Wed Jan  9 09:40:21 2013 tolsa_c
*/

#include <TcpSocket.h>

TcpSocket::TcpSocket()
{
#ifdef PLATFORM_LINUX
  this->_asocket = new TcpSocketUnix;
#endif
  
#ifdef PLATFORM_WIN32
  this->_asocket = new TcpSocketWin;
#endif
}

TcpSocket::TcpSocket(socket_t s)
{
#ifdef PLATFORM_LINUX
  this->_asocket = new TcpSocketUnix(s);
#endif
  
#ifdef PLATFORM_WIN32
  this->_asocket = new TcpSocketWin(s);
#endif
}

TcpSocket::~TcpSocket()
{}

bool		TcpSocket::connectSocket(const std::string& ip, int port)
{
  return (this->_asocket->connectSocket(ip, port));
}

bool		TcpSocket::block()
{
  return (this->_asocket->block());
}


bool		TcpSocket::unblock()
{
  return (this->_asocket->unblock());
}

int		TcpSocket::read(char *buff, int size)
{
  return (this->_asocket->read(buff, size));
}

int		TcpSocket::readAll(char *buff)
{
  return (this->_asocket->readAll(buff));
}

int		TcpSocket::write(const std::string& data, int size)
{
  return (this->_asocket->write(data, size));
}

int		TcpSocket::writePacket(PacketContainer::PacketSerialised *p)
{
  return (this->_asocket->writePacket(p));
}

int		TcpSocket::copyQueue(char *buff, int size)
{
  return (this->_asocket->copyQueue(buff, size));
}

bool		TcpSocket::dataAvailable()
{
  return (this->_asocket->dataAvailable());
}

int		TcpSocket::bytesAvailable()
{
  return (this->_asocket->bytesAvailable());
}

int		TcpSocket::closeSocket()
{
  return (this->_asocket->closeSocket());
}

void		TcpSocket::flush()
{
  return (this->_asocket->flush());
}

socket_t	TcpSocket::getSocket() const
{
  return (this->_asocket->getSocket());
}
