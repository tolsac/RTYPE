/*
** TcpServer.h for TcpServer in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:44:26 2012 tolsa_c
** Last update Thu Jan 10 00:57:43 2013 tolsa_c
*/

#ifndef TCPSERVERWIN_H_
# define TCPSERVERWIN_H_

#define _WINSOCKAPI_ 
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <map>
#include <ws2tcpip.h>
#include <ATcpServer.h>
#pragma comment(lib,"Ws2_32.lib")

class TcpServerWin : public ATcpServer
{
public:
  TcpServerWin();
  TcpServerWin(std::list<Connexion*>*, std::list<PacketInfo*>*);
  ~TcpServerWin();

  bool					start();
  bool					start(int, int);
  bool					UdpListener(UdpSocket*);
  void					setPacketList(std::list<PacketInfo*>*);
  void					setConnexionList(std::list<Connexion*>*);
  bool					bindSocket(int);
  bool					listenSocket(int);
  void					acceptSocket();
  bool					checkMagic(uint32_t);
  std::list<Connexion*>::iterator&	readPacketTcp(std::list<Connexion*>::iterator&);
  void					readPacketUdp();
  void					sendPacketTcp(PacketContainer::PacketSerialised*, Connexion*);
  void					sendPacketUdp(PacketContainer::PacketSerialised*, Connexion*);
  void					run();
};

#endif /* !TCPSERVER_H_ */
