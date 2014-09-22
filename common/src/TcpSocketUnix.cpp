/*
** TcpSocket.cpp for TcpSocket in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:39:17 2012 tolsa_c
** Last update Wed Jan 16 07:32:55 2013 tolsa_c
*/

#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <errno.h>
#include <TcpSocketUnix.h>
#include <netdb.h>


TcpSocketUnix::TcpSocketUnix()
{
  struct protoent	*p;

  p = getprotobyname("TCP");
  this->_valid = true;
  this->_socket = socket(AF_INET, SOCK_STREAM, p->p_proto);
  if (this->_socket <= 0)
    this->_valid = false;
  //  if (!this->unblock())
  //  this->_valid = false;
}

TcpSocketUnix::TcpSocketUnix(socket_t s)
{
  this->_valid = true;
  this->_socket = s;
  if (!this->unblock())
    this->_valid = false;
}

TcpSocketUnix::~TcpSocketUnix()
{
  this->closeSocket();
}

bool			TcpSocketUnix::block()
{
  if (fcntl(this->_socket, F_SETFL, O_NONBLOCK, 0) == -1)
    return (false);
  return (true);
}

bool			TcpSocketUnix::unblock()
{
  if (fcntl(this->_socket, F_SETFL, O_NONBLOCK, 1) == -1)
    return (false);
  return (true);
}

bool			TcpSocketUnix::connectSocket(const std::string& ip, int port)
{
  struct sockaddr_in	srv;
  int			ret;

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = inet_addr(ip.c_str());
  srv.sin_port = htons(port);
  if ((ret = connect(this->_socket, (struct sockaddr *)&srv, sizeof(srv))) == -1)
    perror("connect");
  if (ret == 0)
    return (true);
  return (false);
}

int			TcpSocketUnix::read(char *buff, int len)
{
  int			ret;

  ret = recv(this->_socket, buff, len, 0);
  return (ret);
}

int			TcpSocketUnix::bytesAvailable()
{
  int			ret;
  char			buff[65536];

  ret = recv(this->_socket, buff, 65535, MSG_PEEK);
  return (ret);
}

int			TcpSocketUnix::copyQueue(char *buff, int len)
{
  return (recv(this->_socket, buff, 65535, MSG_PEEK));
}

int			TcpSocketUnix::readAll(char *buff)
{
  return (this->read(buff, 65535));
}

int			TcpSocketUnix::write(const std::string& buff, int len)
{
  int			ret;
  
  ret = send(this->_socket, buff.c_str(), len, 0);
  return (ret);
}

int			TcpSocketUnix::writePacket(PacketContainer::PacketSerialised *packet)
{
  int			ret;

  ret = 0;
  ret += send(this->_socket, (&packet->header.magic), sizeof(uint32_t), 0);
  ret += send(this->_socket, (&packet->header.checksum), sizeof(uint32_t), 0);
  ret += send(this->_socket, (&packet->header.timestamp), sizeof(uint32_t), 0);
  ret += send(this->_socket, (&packet->header.commandId), sizeof(uint16_t), 0);
  ret += send(this->_socket, (&packet->header.dataSize), sizeof(uint16_t), 0);
  ret += send(this->_socket, (packet->data), packet->header.dataSize, 0);
  if (ret != (int)(sizeof(PacketContainer::Header) + packet->header.dataSize))
    return (-1);
  return (ret);
}

bool			TcpSocketUnix::dataAvailable()
{
  fd_set                sready;
  struct timeval        nowait;

  FD_ZERO(&sready);
  FD_SET((unsigned int)this->_socket, &sready);
  memset((char *)&nowait, 0, sizeof(nowait));
  select(this->_socket + 1, &sready, NULL, NULL, &nowait);
  if (FD_ISSET(this->_socket, &sready))
    return (true);
  else
    return (false);
}

int			TcpSocketUnix::closeSocket()
{
  return (close(this->_socket));
}

socket_t		TcpSocketUnix::getSocket() const
{
  return (this->_socket);
}

void			TcpSocketUnix::flush()
{
  char			buff[65536];
  int			bav;

  bav = this->bytesAvailable();
  this->read(buff, bav);
}
