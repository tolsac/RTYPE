/*
** circularBuffer.h for circularBuffer in /home/tolsa/Documents/R-type/Network/libsocket/only_srv/Buffer
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Sat Dec 22 14:31:25 2012 tolsa_c
** Last update Fri Jan  4 04:50:30 2013 tolsa_c
*/

#ifndef BUFFER_H_
# define BUFFER_H_

#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include <PacketContainer.h>

template<typename T, int _size>
class circularBuffer
{
public:
	circularBuffer()
	{
		_indexR = 0;
		_indexW = 0;
		memset(_buff, 0 , _size);
	}

	~circularBuffer()
	{}

	int				circular_memcpy(T *dest, T *src, int n)
	{
		int			i;
		int			back_iR;

		back_iR = _indexR;
		i = -1;
		while (++i < n)
		{
			dest[i] = src[_indexR];
			_indexR = (_indexR + 1) % _size;
		}
		_indexR = back_iR;
		return (n);
	}

	template<typename X>
	void				append(X arg, int len)
	{
		append(&arg, len);
	}

	template<typename X>
	void				append(X* arg, int len)
	{
		char		*unknow_type_arg;
		int			i;

		i = -1;
		unknow_type_arg = reinterpret_cast<T*>(arg);
		while (++i < len)
		{
			this->_buff[_indexW] = unknow_type_arg[i];
			_indexW = (_indexW + 1) % _size;
		}
	}

	T				*get(int size)
	{
		T				*_data;

		_data = new T[size];
		circular_memcpy(_data, this->_buff, size);
		return (_data);
	}

	T				*extract(int size)
	{
		T				*_data;
		int				n;

		_data = new T[size];
		n = circular_memcpy(_data, this->_buff, size);
		_indexR = (_indexR + n) % _size;
		return (_data);
	}

	unsigned int			size()
	{
		//std::cout << "buffcircsize " << abs(((_indexW + _size) - _indexR) % _size) << std::endl;
		if (_indexW < _indexR)
			return (abs(((_indexW + _size) - _indexR) % _size));
		return (abs((_indexW - _indexR) % _size));
	}
private:
	T				_buff[_size];
	int				_indexR;
	int				_indexW;
};

#endif /* !BUFFER_H_ */
