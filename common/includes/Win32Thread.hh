#ifndef		__WIN32THREAD__
#define		__WIN32THREAD__

#include <winsock2.h>
#include <Windows.h>
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
	HANDLE			_thread;
	ICallback*		_task;
};

#endif		//__WIN32THREAD__