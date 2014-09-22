#include	"UnixMutex.hh"
#include	<iostream>

MutexUnix::MutexUnix()
{
  pthread_mutex_init(&this->_mutex, NULL);
}

MutexUnix::~MutexUnix()
{
  pthread_mutex_destroy(&this->_mutex);
}

bool	MutexUnix::lock()
{
  if (!pthread_mutex_lock(&this->_mutex))
    return true;
  return false;
}

bool	MutexUnix::trylock()
{
  if (!pthread_mutex_lock(&this->_mutex))
    return true;
  return false;
}

bool	MutexUnix::unlock()
{
  if (!pthread_mutex_unlock(&this->_mutex))
    return true;
  return false;
}
