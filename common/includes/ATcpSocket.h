/*
** ITcpSocket.h for ITcpSocket in /home/tolsa/Documents/R-type/newSock
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 04:22:51 2013 tolsa_c
** Last update Thu Jan 10 00:56:44 2013 tolsa_c
*/

#ifndef ITCPSOCKET_H_
# define ITCPSOCKET_H_

#include <string>
#include <ASocket.h>
#include <PacketContainer.h>

class ATcpSocket : public ASocket
{
public:
  virtual bool          connectSocket(const std::string&, int) = 0;
  virtual bool          block() = 0;
  virtual bool          unblock() = 0;
  virtual int           read(char *, int) = 0;
  virtual int           readAll(char *) = 0;
  virtual int           write(const std::string& , int) = 0;
  virtual int           writePacket(PacketContainer::PacketSerialised*) = 0;
  virtual int           copyQueue(char*, int) = 0;
  virtual bool          dataAvailable() = 0;
  virtual int           bytesAvailable() = 0;
  virtual int           closeSocket() = 0;
  virtual void          flush() = 0;
  virtual socket_t      getSocket() const = 0;
};

#endif /* !ATCPSOCKET_H_ */
