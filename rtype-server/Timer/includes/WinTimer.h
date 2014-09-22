#pragma once

#include	"IClock.h"

class WinTimer : public IClock
{

public: //public methods

	WinTimer();
	~WinTimer();

	void		reset();
	float		getElapsedTime() const;
	void		sleep(float time) const;

private: //private methods

	float	_getCurrentTime() const;

private: //private attributes

	float	_time;
};
