#pragma once

#include	"IClock.h"

class Clock
{

public: //public methods

	Clock();
	~Clock();

	void	reset();
	float	getElapsedTime() const;
	void	sleep(float time) const;

private: //private attributes

	IClock*	_clock;
};