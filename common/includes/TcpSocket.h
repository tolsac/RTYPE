/*
** TcpSocket.h for TcpSocket in /home/tolsa/Documents/R-type/newSock
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 04:55:50 2013 tolsa_c
** Last update Wed Jan  9 09:38:40 2013 tolsa_c
*/

#ifndef TCPSOCKET_H_
# define TCPSOCKET_H_

#include <Platform.h>
#include <ATcpSocket.h>

#ifdef PLATFORM_LINUX
 #include <TcpSocketUnix.h>
#endif
#ifdef PLATFORM_WIN32
 #include <TcpSocketWin.h>
#endif

class TcpSocket
{
public:
  TcpSocket();
  TcpSocket(socket_t);
  ~TcpSocket();

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

private:
  ATcpSocket	*_asocket; 
};

#endif /* !TCPSOCKET_H_ */
