/*
** UdpSocket.h for  in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@epitech.net>
** 
** Started on  Tue Dec 11 16:01:49 2012 tolsa_c
** Last update Wed Jan  9 09:39:53 2013 tolsa_c
*/

#ifndef __UDPSOCKETUNIX__
#define __UDPSOCKETUNIX__

#ifdef PLATFORM_LINUX
 #include <arpa/inet.h>
#endif
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>
#include <string>
#include <AUdpSocket.h>

class UdpSocketUnix : public AUdpSocket
{
 public:
  UdpSocketUnix();
  UdpSocketUnix(socket_t);
  ~UdpSocketUnix();

  bool          bindSocket(int);
  bool		block();
  bool		unblock();
  int           bytesAvailable();
  bool          dataAvailable();
  int		pendingDatagramSize();
  int           readDatagram(char*, int);
  int           readDatagram(char*, int, sockaddr_in *);
  int           readAll(char*);
  int           writeDatagram(const std::string&, int, const std::string&, int);
  int           writePacket(PacketContainer::PacketSerialised*, const std::string&, int);
  int		closeSocket();
  socket_t	getSocket() const;
};

#endif //__UDPSOCKET__
