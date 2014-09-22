/*
** PacketInfo.h for PacketInfo in /home/tolsa/Documents/R-type/Network/libsocket/only_srv
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 25 11:04:19 2012 tolsa_c
** Last update Wed Jan  9 09:06:31 2013 tolsa_c
*/

#ifndef PACKETINFO_H_
# define PACKETINFO_H_

#include <PacketContainer.h>
#include <Connexion.h>

struct PacketInfo
{
	PacketContainer			*packet;
	Connexion				*connexion;
};



#endif /* !PACKETINFO_H_ */
