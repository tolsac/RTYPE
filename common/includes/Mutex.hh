/*
** Mutex.hh for Mutex in /home/tolsa/rtype-2015-tolsa_c/rtype-server/ThreadPool/includes
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Jan  9 13:29:16 2013 tolsa_c
** Last update Wed Jan  9 13:36:34 2013 tolsa_c
*/

#ifndef MUTEX_HH_
# define MUTEX_HH_

#include <Platform.h>
#include <IMutex.hh>

#ifdef PLATFORM_LINUX
 #include <UnixMutex.hh>
#endif
#ifdef PLATFORM_WIN32
 #include <Win32Mutex.hh>
#endif

class Mutex
{
public:
  Mutex();
  ~Mutex();
  bool			lock();
  bool			trylock();
  bool			unlock();
private:
  IMutex		*_mutex;
};

#endif /* !MUTEX_HH_ */
