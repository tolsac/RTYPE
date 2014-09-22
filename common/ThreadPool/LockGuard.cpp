#include	"LockGuard.h"

LockGuard::LockGuard(Mutex& m)
	: _mutex(m)
{
	this->_mutex.lock();
}


LockGuard::~LockGuard()
{
	this->_mutex.unlock();
}