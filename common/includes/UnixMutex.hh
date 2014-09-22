#ifndef		__UNIXMUTEX__
#define		__UNIXMUTEX__

#include	<pthread.h>
#include	"IMutex.hh"

class	MutexUnix : public IMutex
{
public:
	MutexUnix();
	~MutexUnix();
	virtual	bool		lock();
	virtual	bool		trylock();
	virtual bool		unlock();
private:
	pthread_mutex_t		_mutex;
};

#endif		//__UNIXMUTEX__
