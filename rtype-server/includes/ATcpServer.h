/*
** ITcpServer.h for ITcpServer in /home/tolsa/rtype-2015-tolsa_c/rtype-server/includes
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 22:14:24 2013 tolsa_c
** Last update Wed Jan  9 23:15:54 2013 tolsa_c
*/

#ifndef ITCPSERVER_H_
# define ITCPSERVER_H_

#include <TcpServerAttr.h>

class ATcpServer : public TcpServerAttr
{
public:
  virtual bool                                  start() = 0;
  virtual bool                                  start(int, int) = 0;
  virtual bool                                  UdpListener(UdpSocket*) = 0;
  virtual void                                  setPacketList(std::list<PacketInfo*>*) = 0;
  virtual void                                  setConnexionList(std::list<Connexion*>*) = 0;
  virtual bool                                  bindSocket(int) = 0;
  virtual bool                                  listenSocket(int) = 0;
  virtual void                                  acceptSocket() = 0;
  virtual std::list<Connexion*>::iterator&      readPacketTcp(std::list<Connexion*>::iterator&) = 0;
  virtual void                                  readPacketUdp() = 0;
  virtual void                                  sendPacketTcp(PacketContainer::PacketSerialised*, Connexion*) = 0;
  virtual void                                  sendPacketUdp(PacketContainer::PacketSerialised*, Connexion*) = 0;
  virtual void                                  run() = 0;
};

#endif /* !ITCPSERVER_H_ */
