//
// Rect.hpp for generic in /home/petit_c//projets/c++/bomberman/bomberman-2015-petit_c
// 
// Made by clement petit
// Login   <petit_c@epitech.net>
// 
// Started on  Wed May  9 16:17:21 2012 clement petit
//
//

#ifndef		__RECT_HPP__
#define		__RECT_HPP__

#include	<iostream>
#include	"Vector.hpp"

namespace epi
{
  template<typename T>
  class Rect
  {
  public:
    T		x;
    T		y;
    T		width;
    T		height;

    Rect(T x = 0, T y = 0, T width = 0, T right = 0);
    ~Rect();

    operator	bool() const;
    bool	operator!() const;
    bool	inter(const Rect<T>& rhs) const;

    static const Rect<T>	fromPosition(const Vector2<T>& pos, const Vector2<T>& size);
  };

  template<typename T>
  std::ostream&			operator<<(std::ostream& os, const Rect<T>& r)
  {
    os << "Rect4 : x = " << r.x << " y = " << r.y << " width = " << r.width << " height = " << r.height;
    return (os);
  }

  template<typename T>
  Rect<T>::Rect(T x, T y, T width, T height)
    : x(x),
      y(y),
      width(width),
      height(height)
  {
  }

  template<typename T>
  Rect<T>::~Rect()
  {
  }

  template<typename T>
  Rect<T>::operator bool() const
  {
    return (this->width || this->height);
  }
  
  template<typename T>
  bool			Rect<T>::operator!() const
  {
    return (!static_cast<bool>(*this));
  }

  template<typename T>
  bool			Rect<T>::inter(const Rect<T>& rhs) const
  {
    if ((rhs.x >= this->x + this->width)
       || (rhs.x + rhs.width <= this->x)
       || (rhs.y >= this->y + this->height)
       || (rhs.y + rhs.height <= this->y))
      {
		return false;
      }
    else
      {
		return true;
      }
  }

  template<typename T>
  const Rect<T>		Rect<T>::fromPosition(const Vector2<T>& pos, const Vector2<T>& size)
  {
    return (Rect<T>(pos.x, pos.y, size.x, size.y));
  }

  typedef Rect<int>	Rect4i;
  typedef Rect<float>	Rect4f;
  typedef Rect<double>	Rect4d;

}

#endif		//__RECT_HPP__
