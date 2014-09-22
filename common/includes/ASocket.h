/*
** ASocket.h for ASocket in /home/tolsa/Documents/R-type/newSock
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Jan  8 05:31:12 2013 tolsa_c
** Last update Wed Jan  9 20:53:16 2013 tolsa_c
*/

#ifndef ASOCKET_H_
# define ASOCKET_H_

#include <Platform.h>

#ifdef PLATFORM_LINUX
 typedef int socket_t;
#endif
#ifdef PLATFORM_WIN32
#include <WinSock2.h>
 typedef SOCKET socket_t;
#endif

class ASocket
{
protected:
  socket_t		_socket;
  bool			_valid;
};

#endif /* !ASOCKET_H_ */
