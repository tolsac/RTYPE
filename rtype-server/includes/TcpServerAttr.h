/*
** ATcpServer.h for ATcpServer in /home/tolsa/rtype-2015-tolsa_c/rtype-server/includes
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 22:08:10 2013 tolsa_c
** Last update Wed Jan  9 23:19:05 2013 tolsa_c
*/

#ifndef ATCPSERVERATTR_H_
# define ATCPSERVERATTR_H_

#include <list>
#include <map>
#include <PacketInfo.h>
#include <UdpSocket.h>
#include <circularBuffer.hpp>

typedef circularBuffer<char, 512> buffer_t;

class TcpServerAttr
{
protected:
  int                                   _tcpSocket;
  UdpSocket                             *_udpSocket;
  std::list<Connexion*>                 *_lstConnexions;
  std::list<PacketInfo*>                *_lstPackets;
  std::map<short int, buffer_t>         _buffers;
};

#endif /* !ATCPSERVERATTR_H_ */
