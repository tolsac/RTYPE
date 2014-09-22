#include "WinTimer.h"
#include <winsock2.h>
#include <Windows.h>

WinTimer::WinTimer(void)
{
	this->reset();
}


WinTimer::~WinTimer(void)
{
}

void		WinTimer::reset()
{
	this->_time = this->_getCurrentTime();
}


float		WinTimer::getElapsedTime() const
{
	return (this->_getCurrentTime() - this->_time);
}

float		WinTimer::_getCurrentTime() const
{
	LARGE_INTEGER f;
    BOOL          ret = QueryPerformanceFrequency(&f);

    if (ret)
    {
        LARGE_INTEGER currtime;
        QueryPerformanceCounter(&currtime);

        return static_cast<float>(currtime.QuadPart) / f.QuadPart;
    }
    else
    {
        return GetTickCount() * 0.001f;
    }
}

void		WinTimer::sleep(float time) const
{
	Sleep((DWORD) (time * 1000));
}
