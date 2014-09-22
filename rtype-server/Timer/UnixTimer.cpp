#include	"UnixTimer.h"
#include	<sys/time.h>

UnixTimer::UnixTimer()
{
  this->reset();  
}

UnixTimer::~UnixTimer()
{
}

void            UnixTimer::reset()
{
  this->_time = this->_getCurrentTime();
}


float           UnixTimer::getElapsedTime() const
{
  return (this->_getCurrentTime() - this->_time);
}

#include	<iostream>

float		UnixTimer::_getCurrentTime() const
{
  struct timespec tmbuff;

  tmbuff.tv_sec = 0;
  tmbuff.tv_nsec = 0;
  clock_gettime(CLOCK_MONOTONIC, &tmbuff);
  return (tmbuff.tv_sec + tmbuff.tv_nsec / 1000 / 1000000.0f);
}

void		UnixTimer::sleep(float time) const
{
  usleep(time * 1000);
}
