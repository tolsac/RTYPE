/*
** TcpServer.h for TcpServer in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:44:26 2012 tolsa_c
** Last update Wed Jan  9 23:30:29 2013 tolsa_c
*/

#ifndef TCPSERVERUNIX_H_
# define TCPSERVERUNIX_H_

#ifdef PLATFORM_LINUX
 #include <arpa/inet.h>
#endif
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <iostream>

#include <ATcpServer.h>

class TcpServerUnix : public ATcpServer
{
public:
  TcpServerUnix();
  TcpServerUnix(std::list<Connexion*>*, std::list<PacketInfo*>*);
  ~TcpServerUnix();

  bool					start();
  bool					start(int, int);
  bool					UdpListener(UdpSocket*);
  void					setPacketList(std::list<PacketInfo*>*);
  void					setConnexionList(std::list<Connexion*>*);
  bool					bindSocket(int);
  bool					listenSocket(int);
  void					acceptSocket();
  std::list<Connexion*>::iterator&	readPacketTcp(std::list<Connexion*>::iterator&);
  void					readPacketUdp();
  void					sendPacketTcp(PacketContainer::PacketSerialised*, Connexion*);
  void					sendPacketUdp(PacketContainer::PacketSerialised*, Connexion*);
  void					run();
};

#endif /* !TCPSERVERUNIX_H_ */
