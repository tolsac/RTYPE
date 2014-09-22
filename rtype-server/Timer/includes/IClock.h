#pragma once

class IClock
{

public: //public methods

	virtual ~IClock() {}

	virtual void	reset() = 0;
	virtual float	getElapsedTime() const = 0;
	virtual void	sleep(float time) const = 0;
};
