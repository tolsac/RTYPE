/*
** TcpSocketWin.h for TcpSocketWin in /home/tolsa/Documents/R-type/newSock/new
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 05:41:44 2013 tolsa_c
** Last update Wed Jan  9 09:39:27 2013 tolsa_c
*/

#ifndef TCPSOCKETWIN_H_
# define TCPSOCKETWIN_H_

#include <winsock2.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <ws2tcpip.h>
#include <PacketContainer.h>
#include <ATcpSocket.h>
#pragma comment(lib,"Ws2_32.lib")

class TcpSocketWin : public ATcpSocket
{
public:
  TcpSocketWin();
  TcpSocketWin(socket_t);
  ~TcpSocketWin();

  bool          connectSocket(const std::string&, int);
  bool          block();
  bool          unblock();
  int           read(char *, int);
  int           readAll(char *);
  int           write(const std::string& , int);
  int           writePacket(PacketContainer::PacketSerialised*);
  int           copyQueue(char*, int);
  bool          dataAvailable();
  int           bytesAvailable();
  int           closeSocket();
  void          flush();
  socket_t      getSocket() const;
};

#endif /* !TCPSOCKETWIN_H_ */
