/*
** Singleton.hpp for Singleton in /home/tolsa/Documents/R-type/Network/libsocket/only_srv
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Wed Dec 26 15:11:14 2012 tolsa_c
** Last update Wed Dec 26 15:16:20 2012 tolsa_c
*/

#ifndef SINGLETON_HPP_
# define SINGLETON_HPP_

#include <cstdio>

template <typename T>
class Singleton
{
protected:
  Singleton () {}
  ~Singleton () {}

public:
  static T *getInstance()
  {
    if (NULL == _singleton)
      _singleton = new T;
    return (static_cast<T*> (_singleton));
  }
  static void killInstance()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

private:
  static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#endif /* !SINGLETON_HPP_ */
