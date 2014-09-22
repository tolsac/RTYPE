/*
** Mutex.cpp for Mutex in /home/tolsa/rtype-2015-tolsa_c/rtype-server/ThreadPool
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 13:28:09 2013 tolsa_c
** Last update Wed Jan  9 13:35:13 2013 tolsa_c
*/

#include <Mutex.hh>

Mutex::Mutex()
{
#ifdef PLATFORM_LINUX
  this->_mutex = new MutexUnix;
#endif
#ifdef PLATFORM_WIN32
  this->_mutex = new MutexWin32;
#endif
}

Mutex::~Mutex()
{
  delete this->_mutex;
}

bool			Mutex::lock()
{
  return (this->_mutex->lock());
}

bool			Mutex::trylock()
{
  return (this->_mutex->trylock());
}

bool			Mutex::unlock()
{
  return (this->_mutex->unlock());
}
