#pragma once

#include	"IClock.h"

class UnixTimer : public IClock
{
public: //public methods

  UnixTimer();
  ~UnixTimer();

  void	reset();
  float	getElapsedTime() const;
  void	sleep(float time) const;

private: //private methods

  float	_getCurrentTime() const;

private: //private attributes

  float	_time;
};
