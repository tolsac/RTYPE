/*
** AUdpSocket.h for AUdpSocket in /home/tolsa/Documents/R-type/newSock/udp
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 07:16:12 2013 tolsa_c
** Last update Thu Jan 10 00:57:07 2013 tolsa_c
*/

#ifndef AUDPSOCKET_H_
# define AUDPSOCKET_H_

#include <string>
#include <ASocket.h>
#include <PacketContainer.h>
#include <fcntl.h>
#include <Platform.h>

#ifdef PLATFORM_LINUX
 #include <arpa/inet.h>
#endif

class AUdpSocket : public ASocket
{
public:
  virtual bool          bindSocket(int) = 0;
  virtual bool          block() = 0;
  virtual bool          unblock() = 0;
  virtual int           bytesAvailable() = 0;
  virtual bool          dataAvailable() = 0;
  virtual int           pendingDatagramSize() = 0;
  virtual int           readDatagram(char*, int) = 0;
  virtual int           readDatagram(char*, int, sockaddr_in *) = 0;
  virtual int           readAll(char*) = 0;
  virtual int           writeDatagram(const std::string&, int, const std::string&, int) = 0;
  virtual int           writePacket(PacketContainer::PacketSerialised*, const std::string&, int) = 0;
  virtual int           closeSocket() = 0;
  virtual socket_t      getSocket() const = 0;
};

#endif /* !AUDPSOCKET_H_ */
