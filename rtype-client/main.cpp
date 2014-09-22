/*
** main.cpp for  in /home/tolsa/rtype-2015-tolsa_c/rtype-client
** 
** Made by tolsa_c
** Login   <tolsa@epitech.net>
** 
** Started on  Wed Jan 16 04:24:17 2013 tolsa_c
** Last update Wed Jan 16 04:24:23 2013 tolsa_c
*/

#include	"Client.h"

int		main(int ac, char **av)
{
  Client	*clt;

  clt = new Client;
  clt->init();
  clt->run();
  return (0);
}
