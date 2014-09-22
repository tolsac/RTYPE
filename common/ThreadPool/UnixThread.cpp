#include	<iostream>
#include	"UnixThread.hh"

static void*	runCallback(void* arg)
{
  IThread* thread = (IThread*) arg;
  thread->getTask()->operator()();
  thread->setRunning(false);
}

Thread::Thread()
{
  this->_running = false;
}

Thread::~Thread()
{
}

void    Thread::join()
{
  if (this->_running)
    pthread_join(this->_thread, NULL);
}

void	Thread::start(ICallback* callback)
{
  int err;
  this->_task = callback;
  this->_running = true;
  if ((err = pthread_create(&this->_thread, NULL, &runCallback, this)))
    std::cerr << "Thread creation failed with error code " << err << "." << std::endl;
}

void	Thread::stop()
{
  pthread_cancel(this->_thread);
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
