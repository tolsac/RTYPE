/* Header global du NetworkManager.h. */
/* Auteur: Erick Clarivet */
/* Commencé le 06/01/13. */
/* Dernière modification: 06/01/13. */

#pragma once

#include				<list>

#include <TcpSocket.h>
#include <UdpSocket.h>
#include <circularBuffer.hpp>
#include <ICallback.hh>
#include <ActionManager.h>

class					NetworkManager : public ICallback
{
  ActionManager			*aManager;
  UdpSocket*			udpSocket;
  TcpSocket*			tcpSocket;
  std::string			ip;
  int				port;
  std::list<PacketContainer*>	packets;
  typedef circularBuffer<char, 512> buffer_t;
  buffer_t			bufferTcp;
  buffer_t			bufferUdp;

public:
  NetworkManager();
  ~NetworkManager(void);

  void				setActionManager(ActionManager*);
  void				operator()();
  bool				init(const std::string& ip, int port);
  bool				bindSocket(int port);
  void				run();
  void				update();
  void				sendPacket(PacketContainer*, bool TCP);
  void				sendPacketTcp(PacketContainer*);
  void				sendPacketUdp(PacketContainer*);
  PacketContainer::PacketSerialised*	getPacket();
  void				readPacketTcp();
  void				readPacketUdp();
  std::list<PacketContainer*>&				getPacketList();
  int					getPacketAvailableCount();
  bool				checkMagic(uint32_t magic);
};

