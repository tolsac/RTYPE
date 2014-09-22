/* created by tolsa_c 03/01/2013 */
/* last edit  ... */

#ifndef __UDPSOCKETWIN__
#define __UDPSOCKETWIN__

#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <AUdpSocket.h>
#pragma comment(lib,"Ws2_32.lib")

class UdpSocketWin : public AUdpSocket
{
 public:
  UdpSocketWin();
  UdpSocketWin(socket_t);
  ~UdpSocketWin();

  bool          bindSocket(int);
  bool   		block();
  bool	    	unblock();
  int           bytesAvailable();
  bool          dataAvailable();
  int		    pendingDatagramSize();
  int           readDatagram(char*, int);
  int           readDatagram(char*, int, sockaddr_in *);
  int           readAll(char*);
  int           writeDatagram(const std::string&, int, const std::string&, int);
  int           writePacket(PacketContainer::PacketSerialised*, const std::string&, int);
  int		    closeSocket();
  SOCKET	    getSocket() const;

 private:
  SOCKET	_socket;
  bool		_valid;
};

#endif //__UDPSOCKET__
