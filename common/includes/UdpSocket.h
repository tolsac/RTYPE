/*
** UdpSocket.h for UdpSocket in /home/tolsa/Documents/R-type/newSock/udp
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 07:23:23 2013 tolsa_c
** Last update Wed Jan  9 09:38:54 2013 tolsa_c
*/

#ifndef UDPSOCKET_H_
# define UDPSOCKET_H_

#include <Platform.h>
#include <AUdpSocket.h>

#ifdef PLATFORM_LINUX
 #include <UdpSocketUnix.h>
#endif
#ifdef PLATFORM_WIN32
 #include <UdpSocketWin.h>
#endif

class UdpSocket
{
public:
  UdpSocket();
  UdpSocket(socket_t);
  ~UdpSocket();

  bool          bindSocket(int);
  bool          block();
  bool          unblock();
  int           bytesAvailable();
  bool          dataAvailable();
  int           pendingDatagramSize();
  int           readDatagram(char*, int);
  int           readDatagram(char*, int, sockaddr_in *);
  int           readAll(char*);
  int           writeDatagram(const std::string&, int, const std::string&, int);
  int           writePacket(PacketContainer::PacketSerialised*, const std::string&, int);
  int           closeSocket();
  socket_t      getSocket() const;

private:
  AUdpSocket		*_asocket;
};

#endif /* !UDPSOCKET_H_ */
