#ifndef		__ITHREAD__
#define		__ITHREAD__

#include	"ICallback.hh"

class	IThread
{
public:
	virtual	void		join() = 0;
	virtual void		start(ICallback*) = 0;
	virtual	void		stop() = 0;
	virtual bool		isRunning() const = 0;
	virtual	void		setRunning(bool) = 0;
	virtual ICallback*	getTask() const = 0;
};

#endif		//__ITHREAD__