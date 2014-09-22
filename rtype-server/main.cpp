/*
** main.cpp for main in /home/tolsa/Documents/R-type/Network/libsocket/only_srv
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Dec 19 09:58:08 2012 tolsa_c
** Last update Fri Jan 18 00:24:00 2013 tolsa_c
*/

#include <iostream>
#include <GlobalServerIncludes.h>
#include <Server.h>
#include <cstdlib>

void test()
{
	RoomManager	rm;
	Room*		roomlol = rm.createRoom("lol", new Connexion(), 12, 1);

	roomlol->addClient(new Connexion());
	roomlol->addClient(new Connexion());

	roomlol->launchGame();

	getchar();

	roomlol->stop();

}


int main(int ac, char **av)
{
	
	Server		*srv;

	srv = new Server;
	srv->init();
	srv->run();
}
