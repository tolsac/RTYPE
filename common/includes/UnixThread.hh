#ifndef		__UNIXTHREAD__
#define		__UNIXTHREAD__

#include	<pthread.h>
#include	"IThread.hh"

class	Thread	: public IThread
{
public:
	Thread();
	~Thread();
	virtual	void		join();
	virtual void		start(ICallback*);
	virtual	void		stop();
	virtual bool		isRunning() const;
	virtual	void		setRunning(bool);
	virtual ICallback*	getTask() const;
private:
	bool			_running;
	pthread_t		_thread;
	ICallback*		_task;
};

#endif		//__UNIXTHREAD__
