/* Header global du Client.h. */
/* Auteur: Erick Clarivet */
/* Commencé le 06/01/13. */
/* Dernière modification: 06/01/13. */

#pragma once

#include				<Platform.h>
#ifdef PLATFORM_WIN32
 #include				<winsock2.h>
 #include				<ws2tcpip.h>
#endif

#include				<cstdio>
#include				<map>
#include				<iostream>
#include				<string>
#include				<list>
#include				<sys/types.h>
#include				<fcntl.h>
#include				<iostream>
#include				<SFML/Window.hpp>
#include				<SFML/System.hpp>
#include				<SFML/Graphics.hpp>
#include				"circularBuffer.hpp"
#include				"NetworkManager.h"
#include				"PacketFactory.h"
#include				"Singleton.hpp"
#include				"ThreadPool.hh"
#include				"Graphic.h"

class					Client
{
private:
  Graphics				*_graphic;
  Singleton<NetworkManager>		*_nManager;
  ThreadPool				*_tPool;
  ActionManager				*_aManager;

public:
  Client(void);
  ~Client(void);

  bool				init();
  void				run();
  
  static std::string		getLogin();
  static std::string		login;
  static std::string		roomName;
};
