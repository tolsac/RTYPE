#include	"Win32Mutex.hh"
#include	<iostream>

MutexWin32::MutexWin32()
{
	this->_mutex = NULL;
	this->_mutex = CreateMutex(NULL, false, NULL);
	if (this->_mutex == NULL)
		std::cerr << "CreateMutex error code " << GetLastError() << std::endl;
}

MutexWin32::~MutexWin32()
{
	CloseHandle(this->_mutex);
}

bool	MutexWin32::lock()
{
	DWORD dwWaitResult = WaitForSingleObject(this->_mutex, INFINITE);
	if (dwWaitResult == WAIT_OBJECT_0)
		return true;
	std::cerr << "Coundn't lock mutex, error code: " << GetLastError() << std::endl;
	return false;
}

bool	MutexWin32::trylock()
{
	DWORD dwWaitResult = WaitForSingleObject(this->_mutex, 1);
	if (dwWaitResult == WAIT_OBJECT_0)
		return true;
	return false;
}

bool	MutexWin32::unlock()
{
	if (!ReleaseMutex(this->_mutex))
	//{
		//std::cerr << "Coundn't release the mutex, error code: " << GetLastError() << std::endl;
		return false;
	//}
	return true;
}
