/*
** UdpSocket.cpp for  in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@epitech.net>
** 
** Started on  Thu Dec 13 06:29:03 2012 tolsa_c
** Last update Wed Jan  9 09:40:58 2013 tolsa_c
*/

#include <netdb.h>
#include <UdpSocketUnix.h>

UdpSocketUnix::UdpSocketUnix()
{
  struct protoent	*p;
  
  p = getprotobyname("UDP");
  this->_valid = true;
  this->_socket = socket(AF_INET, SOCK_DGRAM, p->p_proto);
  if (this->_socket <= 0)
    this->_valid = false;
  // if (!this->unblock())
  //   this->_valid = false;
}

UdpSocketUnix::UdpSocketUnix(socket_t s)
{
  this->_valid = true;
  this->_socket = s;
  if (this->_socket <= 0)
    this->_valid = false;
  // if (!this->unblock())
  //   this->_valid = false;
}

UdpSocketUnix::~UdpSocketUnix()
{
  this->closeSocket();
}

bool			UdpSocketUnix::block()
{
  if (fcntl(this->_socket, F_SETFL, O_NONBLOCK, 0) == -1)
    return (false);
  return (true);
}

bool			UdpSocketUnix::unblock()
{
  if (fcntl(this->_socket, F_SETFL, O_NONBLOCK, 1) == -1)
    return (false);
  return (true);
}

bool			UdpSocketUnix::bindSocket(int port)
{
  sockaddr_in		address;
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((unsigned short)port);
  if (bind(this->_socket, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0)
    {
      this->_valid = false;
      return (false);
    }
  return (true);
}

int			UdpSocketUnix::pendingDatagramSize()
{
  int			bytes;
  char			buff[65536];

  bytes = recvfrom(this->_socket, (char*)buff, 65535, MSG_PEEK, NULL, NULL);
  return (bytes);
}

bool			UdpSocketUnix::dataAvailable()
{
  fd_set		sready;
  struct timeval	nowait;

  FD_ZERO(&sready);
  FD_SET((unsigned int)this->_socket, &sready);
  memset((char *)&nowait, 0, sizeof(nowait));
  select(this->_socket + 1, &sready, NULL, NULL, &nowait);
  if (FD_ISSET(this->_socket, &sready))
    return (true);
  else
    return (false);
}

int			UdpSocketUnix::bytesAvailable()
{
  sockaddr_in		from;
  socklen_t		fromLength;
  int			received_bytes;
  char			buff[65536];

  fromLength = sizeof(from);
  received_bytes = recvfrom(this->_socket, (char*)buff, 65536, MSG_PEEK, (sockaddr*)&from, &fromLength);
  return (received_bytes);
}

int			UdpSocketUnix::readDatagram(char *buff, int len)
{
  sockaddr_in		from;
  socklen_t		fromLength;
  int			received_bytes;

  fromLength = sizeof(from);
  received_bytes = recvfrom(this->_socket, (char*)buff, len, 0, (sockaddr*)&from, &fromLength);
  return (received_bytes);
}

int			UdpSocketUnix::readDatagram(char *buff, int len, sockaddr_in *from)
{
  socklen_t		fromLength;
  int			received_bytes;

  fromLength = sizeof(*from);
  received_bytes = recvfrom(this->_socket, (char*)buff, len, 0, (sockaddr*)from, &fromLength);
  return (received_bytes);
}

int			UdpSocketUnix::readAll(char *buff)
{
  sockaddr_in		from;
  socklen_t		fromLength;
  int			received_bytes;

  fromLength = sizeof(from);
  received_bytes = recvfrom(this->_socket, (char*)buff, 65535, 0, (sockaddr*)&from, &fromLength);
  return (received_bytes);
}

int			UdpSocketUnix::writeDatagram(const std::string& buff, int len, const std::string& ip, int port)
{
  struct sockaddr_in	sa;
  
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
  sa.sin_port = htons(port);
  return (sendto(this->_socket, buff.c_str(), len, 0, (sockaddr*)&sa, sizeof(sockaddr_in)));
}

int			UdpSocketUnix::writePacket(PacketContainer::PacketSerialised *p, const std::string& ip, int port)
{
  struct sockaddr_in	sa;
  int			ret;

  ret = 0;
  sa.sin_family = AF_INET;
  inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
  sa.sin_port = htons(port);
  ret += sendto(this->_socket, (&p->header.magic), sizeof(uint32_t), 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  ret += sendto(this->_socket, (&p->header.checksum), sizeof(uint32_t), 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  ret += sendto(this->_socket, (&p->header.timestamp), sizeof(uint32_t), 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  ret += sendto(this->_socket, (&p->header.commandId), sizeof(uint16_t), 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  ret += sendto(this->_socket, (&p->header.dataSize), sizeof(uint16_t), 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  ret += sendto(this->_socket, (p->data), p->header.dataSize, 0, (sockaddr*)&sa, sizeof(sockaddr_in));
  if (ret != (int)(sizeof(PacketContainer::Header) + p->header.dataSize))
    return (-1);
  return (ret);
}

int			UdpSocketUnix::closeSocket()
{
  return (close(this->_socket));
}

socket_t		UdpSocketUnix::getSocket() const
{
  return (this->_socket);
}
