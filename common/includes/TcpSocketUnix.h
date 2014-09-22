/* created by tolsa_c 03/01/2013 */
/* last edit  ... */

#ifndef TCPSOCKETUNIX_H_
# define TCPSOCKETUNIX_H_

#ifdef PLATFORM_LINUX
 #include <arpa/inet.h>
#endif
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <cstring>
#include <string>
#include <ATcpSocket.h>

class TcpSocketUnix : public ATcpSocket
{
public:
  TcpSocketUnix();
  TcpSocketUnix(socket_t);
  ~TcpSocketUnix();

  bool		connectSocket(const std::string&, int);
  bool		block();
  bool		unblock();
  int		read(char *, int);
  int		readAll(char *);
  int		write(const std::string& , int);
  int		writePacket(PacketContainer::PacketSerialised*);
  int		copyQueue(char*, int);
  bool		dataAvailable();
  int		bytesAvailable();
  int		closeSocket();
  void		flush();
  socket_t	getSocket() const;
};

#endif /* !TCPSOCKET_H_ */
