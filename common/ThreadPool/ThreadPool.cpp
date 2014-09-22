#include	"ThreadPool.hh"
#include	"IThread.hh"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
	this->joinAll();
}

int	ThreadPool::getAvailableThreadCount()
{
	int nb = 0;

	for (std::list<IThread*>::iterator it = this->_threads.begin(); it != this->_threads.end(); ++it) {		
		if (!(*it)->isRunning())
			++nb;
	}
	return nb;
}

#include	<iostream>

void	ThreadPool::runTask()
{
	for (std::list<ICallback*>::iterator itc = this->_tasks.begin(); itc != this->_tasks.end(); ++itc) {		
		for (std::list<IThread*>::iterator itt = this->_threads.begin(); itt != this->_threads.end(); ++itt) {	
			if (!(*itt)->isRunning()) {
				(*itt)->start((*itc));
				break;
			}
		}
	}
}

void	ThreadPool::runTask(ICallback* callback)
{
	if (this->getAvailableThreadCount() == 0)
		this->_threads.push_back(new Thread());
	for (std::list<IThread*>::iterator it = this->_threads.begin(); it != this->_threads.end(); ++it) {
		if (!(*it)->isRunning()) {
			(*it)->start(callback);
			return;
		}
	}
}

void	ThreadPool::addTask(ICallback* callback)
{
	this->_tasks.push_back(callback);
	this->_threads.push_back(new Thread());
}

void	ThreadPool::joinAll() const
{
	for (std::list<IThread*>::const_iterator it = this->_threads.begin(); it != this->_threads.end(); ++it) {		
		if ((*it)->isRunning())
			(*it)->join();
	}
}

void	ThreadPool::stopAll() const
{
	for (std::list<IThread*>::const_iterator it = this->_threads.begin(); it != this->_threads.end(); ++it) {		
		if ((*it)->isRunning())
			(*it)->stop();
	}
}
