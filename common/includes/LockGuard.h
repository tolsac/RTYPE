#pragma once

#include	"Mutex.hh"

class LockGuard
{

public: //public methods

	explicit LockGuard(Mutex& m);
	~LockGuard();

private: //private methods

	Mutex& _mutex;
};