#ifndef		__IMUTEX__
#define		__IMUTEX__

class	IMutex
{
public:
	virtual	bool		lock() = 0;
	virtual	bool		trylock() = 0;
	virtual bool		unlock() = 0;
};

#endif		//__ITHREAD__