#ifndef		__WIN32MUTEX__
#define		__WIN32MUTEX__

#include <winsock2.h>
#include <Windows.h>
#include	"IMutex.hh"

class	MutexWin32	: public IMutex
{
public:
	MutexWin32();
	~MutexWin32();
	virtual	bool		lock();
	virtual	bool		trylock();
	virtual bool		unlock();
private:
	HANDLE				_mutex;
};

#endif		//__WIN32MUTEX__
