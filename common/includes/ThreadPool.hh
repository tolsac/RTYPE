#ifndef		__THREADPOOL__
#define		__THREADPOOL__

#include	<list>
#include	<Platform.h>
#include	"ICallback.hh"

#ifdef	PLATFORM_WIN32
 #include	"Win32Thread.hh"
#endif

#ifdef PLATFORM_LINUX
 #include	"UnixThread.hh"
#endif

class	ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	int	getAvailableThreadCount();
	void	runTask();
	void	runTask(ICallback*);
	void	addTask(ICallback*);
	void	joinAll() const;
	void	stopAll() const;
private:
	std::list<IThread*>		_threads;
	std::list<ICallback*>	_tasks;
};

#endif		//__THREADPOOL__
