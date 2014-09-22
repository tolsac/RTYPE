#include	"Clock.h"

#ifdef	WIN32

#include	"WinTimer.h"

Clock::Clock()
	:	_clock(new WinTimer())
{

}

#else

//unix

#include	"UnixTimer.h"

Clock::Clock()
  :	_clock(new UnixTimer())
{
  
}

#endif


Clock::~Clock()
{
	delete this->_clock;
}

void	Clock::reset()
{
	return this->_clock->reset();
}

float	Clock::getElapsedTime() const
{
	return this->_clock->getElapsedTime();
}

void	Clock::sleep(float time) const
{
	return this->_clock->sleep(time);
}