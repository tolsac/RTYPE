#include	<iostream>
#include	"Win32Thread.hh"

void static	runCallback(IThread *);

Thread::Thread()
{
	this->_thread = NULL;
	this->_running = false;
}

Thread::~Thread()
{
}

void    Thread::join()
{
	if (this->_running)
		WaitForSingleObject(this->_thread, INFINITE);
}

void	Thread::start(ICallback* callback)
{
	this->_task = callback;
	this->_running = true;
	this->_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) &runCallback, this, 0, NULL);
}

void	Thread::stop()
{
	TerminateThread(this->_thread, 0);
	this->_running = false;
}

bool	Thread::isRunning() const
{
	return this->_running;
}

void	Thread::setRunning(bool running)
{
	this->_running = running;
}

ICallback*	Thread::getTask() const
{
	return this->_task;
}

void static	runCallback(IThread* thread)
{
	thread->getTask()->operator()();
	thread->setRunning(false);
}
