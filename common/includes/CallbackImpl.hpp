#ifndef		__CALLBACKIMPL__
#define		__CALLBACKIMPL__

#include	"ICallback.hh"

template <typename T>
class	CallbackImpl;

template <typename R, typename P>
class	CallbackImpl<R (P)> : public ICallback
{
private:
	R	(*_task)(P);
public:
	
	CallbackImpl(R (*task)(P)){
		this->_task = task;
	};

	~CallbackImpl(){};

	void operator()(P p){
		this->_task(p);
	};
};

#endif		//__CALLBACKIMPL__