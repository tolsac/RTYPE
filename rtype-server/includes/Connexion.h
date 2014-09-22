/*
** connexion.h for connexion in /home/tolsa/Documents/R-type/Network
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Mon Dec 17 12:38:16 2012 tolsa_c
** Last update Tue Jan  8 09:00:56 2013 tolsa_c
*/

#ifndef CONNEXION_H_
# define CONNEXION_H_

#include <string>

#include <TcpSocket.h>
#include <UdpSocket.h>
#include <circularBuffer.hpp>

class Connexion;
typedef circularBuffer<char, 512> buffer_t;

class Connexion
{
public:
  Connexion();
  ~Connexion();

  std::string			getLogin() const;
  std::string			getIp() const;
  int				getPort() const;
  TcpSocket			*getSocket() const;

  void				setLogin(std::string const&);
  void				setIp(std::string const&);
  void				setPort(int);
  void				setSocket(TcpSocket*);
  buffer_t&			getUdpBuffer();
  buffer_t&			getTcpBuffer();

private:
  buffer_t			tcpbuffer;
  buffer_t			udpbuffer;
  std::string			login;
  std::string			ip;
  int				port;
  TcpSocket			*socket;
};

#endif /* !CONNEXION_H_ */
