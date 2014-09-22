/*
** Connexion.cpp for Connexion in /home/tolsa/Documents/R-type/Network
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Mon Dec 17 12:45:51 2012 tolsa_c
** Last update Sun Dec 30 12:33:08 2012 tolsa_c
*/

#include <Connexion.h>

Connexion::Connexion()
{}

Connexion::~Connexion()
{}

void			Connexion::setLogin(std::string const& l)
{
  this->login = l;
}

void			Connexion::setIp(std::string const& i)
{
  this->ip = i;
}

void			Connexion::setPort(int p)
{
  this->port = p;
}

void			Connexion::setSocket(TcpSocket *sock)
{
  this->socket = sock;
}

TcpSocket		*Connexion::getSocket() const
{
  return (this->socket);
}

std::string		Connexion::getLogin() const
{
  return (this->login);
}

std::string		Connexion::getIp() const
{
  return (this->ip);
}

int			Connexion::getPort() const
{
  return (this->port);
}

buffer_t&		Connexion::getTcpBuffer()
{
  return (this->tcpbuffer);
}


buffer_t&		Connexion::getUdpBuffer()
{
  return (this->udpbuffer);
}
