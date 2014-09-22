/*
** TcpServer.h for TcpServer in /home/tolsa/rtype-2015-tolsa_c/rtype-server/includes
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 22:18:25 2013 tolsa_c
** Last update Wed Jan  9 22:46:37 2013 tolsa_c
*/

#ifndef TCPSERVER_H_
# define TCPSERVER_H_

#include <Platform.h>
#include <ATcpServer.h>

#ifdef PLATFORM_LINUX
 #include <TcpServerUnix.h>
#endif
#ifdef PLATFORM_WIN32
 #include <TcpServerWin.h>
#endif

class TcpServer
{
public:
  TcpServer();
  TcpServer(std::list<Connexion*>*, std::list<PacketInfo*>*);
  ~TcpServer();

  bool                                  start();
  bool                                  start(int, int);
  bool                                  UdpListener(UdpSocket*);
  void                                  setPacketList(std::list<PacketInfo*>*);
  void                                  setConnexionList(std::list<Connexion*>*);
  bool                                  bindSocket(int);
  bool                                  listenSocket(int);
  void                                  acceptSocket();
  std::list<Connexion*>::iterator&      readPacketTcp(std::list<Connexion*>::iterator&);
  void                                  readPacketUdp();
  void                                  sendPacketTcp(PacketContainer::PacketSerialised*, Connexion*);
  void                                  sendPacketUdp(PacketContainer::PacketSerialised*, Connexion*);
  void                                  run();

private:
  ATcpServer				*_atcpServer;
};

#endif /* !TCPSERVER_H_ */
