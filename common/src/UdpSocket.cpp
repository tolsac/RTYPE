/*
** UdpSocket.cpp for UdpSocket in /home/tolsa/Documents/R-type/newSock/udp
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 07:25:27 2013 tolsa_c
** Last update Wed Jan  9 09:40:38 2013 tolsa_c
*/

#include <UdpSocket.h>

UdpSocket::UdpSocket()
{
#ifdef PLATFORM_LINUX
  this->_asocket = new UdpSocketUnix;
#endif

#ifdef PLATFORM_WIN32
  this->_asocket = new UdpSocketWin;
#endif  
}

UdpSocket::UdpSocket(socket_t s)
{
#ifdef PLATFORM_LINUX
  this->_asocket = new UdpSocketUnix(s);
#endif
  
#ifdef PLATFORM_WIN32
  this->_asocket = new UdpSocketWin(s);
#endif
}

UdpSocket::~UdpSocket()
{}

bool		UdpSocket::bindSocket(int port)
{
  return (this->_asocket->bindSocket(port));
}

bool		UdpSocket::block()
{
  return (this->_asocket->block());
}

bool		UdpSocket::unblock()
{
  return (this->_asocket->unblock());
}

int		UdpSocket::bytesAvailable()
{
  return (this->_asocket->bytesAvailable());
}

bool		UdpSocket::dataAvailable()
{
  return (this->_asocket->dataAvailable());
}

int		UdpSocket::pendingDatagramSize()
{
  return (this->_asocket->pendingDatagramSize());
}

int		UdpSocket::readDatagram(char *buff, int size)
{
  return (this->_asocket->readDatagram(buff, size));
}

int		UdpSocket::readDatagram(char *buff, int size, sockaddr_in *from)
{
  return (this->_asocket->readDatagram(buff, size, from));
}

int		UdpSocket::readAll(char *buff)
{
  return (this->_asocket->readAll(buff));
}

int		UdpSocket::writeDatagram(const std::string& data, int size, const std::string& ip, int port)
{
  return (this->_asocket->writeDatagram(data, size, ip, port));
}

int		UdpSocket::writePacket(PacketContainer::PacketSerialised *p, const std::string& ip, int port)
{
  return (this->_asocket->writePacket(p, ip, port));
}

int		UdpSocket::closeSocket()
{
  return (this->_asocket->closeSocket());
}

socket_t	UdpSocket::getSocket() const
{
  return (this->_asocket->getSocket());
}
