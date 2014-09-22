//
// Vector.hh for  in /home/petit_c//persos/generic/bomb
// 
// Made by clement petit
// Login   <petit_c@epitech.net>
// 
// Started on  Mon Mar 19 23:20:24 2012 clement petit
// Last update Tue May 22 14:49:59 2012 guillaume d-eimar-de-jabrun
//

#ifndef		__VECTOR_HPP__
#define		__VECTOR_HPP__

#include	<cmath>
#include	<iostream>

namespace epi
{

  /**
   ** \brief a simple 3 dimension template vector class
   ** 
   ** template<T> :\n
   ** T : the type of coordinate
   **
   */
template <typename T>
struct Vector3
{
public:
  T		x;
  T		y;
  T		z;
public:
  /**
   ** \brief default constructor. If not specified, the coordinate are setted to 0.
   */
  Vector3(T x = 0, T y = 0, T z = 0);
  /**
   ** \brief copy constructor. In template, the type of Vector used for copy 
   */
  template<typename U>
  Vector3(const Vector3<U>& rhs);
  /**
   ** \brief default destructor
   */
  ~Vector3();
  /**
   ** \brief normalize the vector
   */
  void		normalize();
  /**
   ** \brief returns the length of the vector
   */
  T		length() const;
  /**
   ** \brief returns a pointer on an array representing the vector.
   ** This pointer should not be freed
   */
  const T*	toArray() const;
  Vector3&	operator=(const Vector3& rhs);
  Vector3&	operator+=(const Vector3& rhs);
  Vector3&	operator-=(const Vector3& rhs);
  Vector3&	operator*=(const Vector3& rhs);
  Vector3&	operator/=(const Vector3& rhs);
  Vector3&	operator%=(const Vector3& rhs);
  template<typename U>
  Vector3&	operator=(const U& rhs);
  template<typename U>
  Vector3&	operator+=(const U& rhs);
  template<typename U>
  Vector3&	operator-=(const U& rhs);
  template<typename U>
  Vector3&	operator*=(const U& rhs);
  template<typename U>
  Vector3&	operator/=(const U& rhs);
  template<typename U>
  Vector3&	operator%=(const U& rhs);
  bool		operator==(const Vector3& rhs) const;
  bool		operator!=(const Vector3& rhs) const;
  bool		operator>(const Vector3& rhs) const;
  bool		operator<(const Vector3& rhs) const;
  bool		operator>=(const Vector3& rhs) const;
  bool		operator<=(const Vector3& rhs) const;
  operator	bool() const;
};

template <typename T>
Vector3<T>	operator+(const Vector3<T>& lhs);
template <typename T>
Vector3<T>	operator-(const Vector3<T>& lhs);
template <typename T>
Vector3<T>	operator+(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
Vector3<T>	operator-(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
Vector3<T>	operator*(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
Vector3<T>	operator/(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
Vector3<T>	operator%(const Vector3<T>& lhs, const Vector3<T>& rhs);

template <typename T, typename U>
Vector3<T>	operator+(const Vector3<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector3<T>	operator-(const Vector3<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector3<T>	operator*(const Vector3<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector3<T>	operator/(const Vector3<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector3<T>	operator%(const Vector3<T>& lhs, const U& rhs);

template <typename T, typename U>
Vector3<T>	operator+(const U& lhs, const Vector3<T>& rhs);
template <typename T, typename U>
Vector3<T>	operator-(const U& lhs, const Vector3<T>& rhs);
template <typename T, typename U>
Vector3<T>	operator*(const U& lhs, const Vector3<T>& rhs);
template <typename T, typename U>
Vector3<T>	operator/(const U& lhs, const Vector3<T>& rhs);
template <typename T, typename U>
Vector3<T>	operator%(const U& lhs, const Vector3<T>& rhs);

template <typename T>
std::ostream&	operator<<(std::ostream& os, const Vector3<T>& rhs);

  /**
   ** \brief a typedef on a vector 3 float
   */
  typedef	Vector3<float>		Vector3f;
  /**
   ** \brief a typedef on a vector 3 int
   */
  typedef	Vector3<int>		Vector3i;
  /**
   ** \brief a typedef on a vector 3 double
   */
  typedef	Vector3<double>		Vector3d;

  /**
   ** \brief a simple 2 dimension template vector class
   ** 
   ** template<T> :\n
   ** T : the type of coordinate
   **
   */
template <typename T>
struct Vector2
{
public:
  T		x;
  T		y;
public:
  /**
   ** \brief default constructor. If not specified, the coordinate are setted to 0.
   */
  Vector2(T x = 0, T y = 0);
  /**
   ** \brief copy constructor. In template, the type of Vector used for copy 
   */
  template<typename U>
  Vector2(const Vector2<U>& rhs);
  /**
   ** \brief default destructor
   */
  ~Vector2();
  /**
   ** \brief normalize the vector
   */
  void		normalize();
  /**
   ** \brief returns the length of the vector
   */
  T		length() const;
  /**
   ** \brief returns a pointer on an array representing the vector.
   ** This pointer should not be freed
   */
  const T*	toArray() const;
  Vector2&	operator=(const Vector2& rhs);
  Vector2&	operator+=(const Vector2& rhs);
  Vector2&	operator-=(const Vector2& rhs);
  Vector2&	operator*=(const Vector2& rhs);
  Vector2&	operator/=(const Vector2& rhs);
  Vector2&	operator%=(const Vector2& rhs);
  template<typename U>
  Vector2&	operator=(const U& rhs);
  template<typename U>
  Vector2&	operator+=(const U& rhs);
  template<typename U>
  Vector2&	operator-=(const U& rhs);
  template<typename U>
  Vector2&	operator*=(const U& rhs);
  template<typename U>
  Vector2&	operator/=(const U& rhs);
  template<typename U>
  Vector2&	operator%=(const U& rhs);
  bool		operator==(const Vector2& rhs) const;
  bool		operator!=(const Vector2& rhs) const;
  bool		operator>(const Vector2& rhs) const;
  bool		operator<(const Vector2& rhs) const;
  bool		operator>=(const Vector2& rhs) const;
  bool		operator<=(const Vector2& rhs) const;
  operator	bool() const;
};

template <typename T>
Vector2<T>	operator+(const Vector2<T>& lhs);
template <typename T>
Vector2<T>	operator-(const Vector2<T>& lhs);
template <typename T>
Vector2<T>	operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);
template <typename T>
Vector2<T>	operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);
template <typename T>
Vector2<T>	operator*(const Vector2<T>& lhs, const Vector2<T>& rhs);
template <typename T>
Vector2<T>	operator/(const Vector2<T>& lhs, const Vector2<T>& rhs);
template <typename T>
Vector2<T>	operator%(const Vector2<T>& lhs, const Vector2<T>& rhs);

template <typename T, typename U>
Vector2<T>	operator+(const Vector2<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector2<T>	operator-(const Vector2<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector2<T>	operator*(const Vector2<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector2<T>	operator/(const Vector2<T>& lhs, const U& rhs);
template <typename T, typename U>
Vector2<T>	operator%(const Vector2<T>& lhs, const U& rhs);

template <typename T, typename U>
Vector2<T>	operator+(const U& lhs, const Vector2<T>& rhs);
template <typename T, typename U>
Vector2<T>	operator-(const U& lhs, const Vector2<T>& rhs);
template <typename T, typename U>
Vector2<T>	operator*(const U& lhs, const Vector2<T>& rhs);
template <typename T, typename U>
Vector2<T>	operator/(const U& lhs, const Vector2<T>& rhs);
template <typename T, typename U>
Vector2<T>	operator%(const U& lhs, const Vector2<T>& rhs);

template <typename T>
std::ostream&	operator<<(std::ostream& os, const Vector2<T>& rhs);

  /**
   ** \brief a typedef on a vector 2 float
   */
  typedef	Vector2<float>		Vector2f;
  /**
   ** \brief a typedef on a vector 2 int
   */
  typedef	Vector2<int>		Vector2i;
  /**
   ** \brief a typedef on a vector 2 unsigned int
   */
  typedef	Vector2<unsigned int>	Vector2ui;
  /**
   ** \brief a typedef on a vector 2 double
   */
  typedef	Vector2<double>		Vector2d;

template <typename T>
Vector3<T>::Vector3(T x, T y, T z)
  : x(x),
    y(y),
    z(z)
{
}

template <typename T>
template<typename U>
Vector3<T>::Vector3(const Vector3<U>& rhs)
  : x(rhs.x),
    y(rhs.y),
    z(rhs.z)
{
}

template <typename T>
Vector3<T>::~Vector3()
{
}

template <typename T>
void		Vector3<T>::normalize()
{
  T		div;

  div = this->length();
  this->x /= div;
  this->y /= div;
  this->z /= div;
}

template <typename T>
T		Vector3<T>::length() const
{
  T		ret;

  ret = this->x * this->x + this->y * this->y + this->z * this->z;
  ret = sqrt(ret);
  return ret;
}

template <typename T>
const T*		Vector3<T>::toArray() const
{
  return reinterpret_cast<const T*>(this);
}

template <typename T>
Vector3<T>&	Vector3<T>::operator=(const Vector3<T>& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}

template <typename T>
Vector3<T>&	Vector3<T>::operator+=(const Vector3<T>& rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;
  this->z += rhs.z;
  return *this;
}

template <typename T>
Vector3<T>&	Vector3<T>::operator-=(const Vector3<T>& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
  return *this;
}

template <typename T>
Vector3<T>&	Vector3<T>::operator*=(const Vector3<T>& rhs)
{
  this->x *= rhs.x;
  this->y *= rhs.y;
  this->z *= rhs.z;
  return *this;
}

template <typename T>
Vector3<T>&	Vector3<T>::operator/=(const Vector3<T>& rhs)
{
  this->x /= rhs.x;
  this->y /= rhs.y;
  this->z /= rhs.z;
  return *this;
}

template <typename T>
Vector3<T>&	Vector3<T>::operator%=(const Vector3<T>& rhs)
{
  this->x %= rhs.x;
  this->y %= rhs.y;
  this->z %= rhs.z;
  return *this;
}

template <typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator+=(const U& rhs)
{
  this->x += rhs;
  this->y += rhs;
  this->z += rhs;
  return *this;
}

template <typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator-=(const U& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
  return *this;
}

template <typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator*=(const U& rhs)
{
  this->x *= rhs;
  this->y *= rhs;
  this->z *= rhs;
  return *this;
}

template <typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator/=(const U& rhs)
{
  this->x /= rhs;
  this->y /= rhs;
  this->z /= rhs;
  return *this;
}

template <typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator%=(const U& rhs)
{
  this->x %= rhs;
  this->y %= rhs;
  this->z %= rhs;
  return *this;
}

template<typename T>
template<typename U>
Vector3<T>&	Vector3<T>::operator=(const U& rhs)
{
  this->x = rhs;
  this->y = rhs;
  this->z = rhs;
  return (*this);
}

template <typename T>
bool		Vector3<T>::operator==(const Vector3<T>& rhs) const
{
  if (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z)
    return true;
  else
    return false;
}

template <typename T>
bool		Vector3<T>::operator!=(const Vector3<T>& rhs) const
{
  if (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z)
    return true;
  else
    return false;
}

template <typename T>
bool		Vector3<T>::operator<(const Vector3<T>& rhs) const
{
  if (this->length() < rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector3<T>::operator>(const Vector3<T>& rhs) const
{
  if (this->length() > rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector3<T>::operator<=(const Vector3<T>& rhs) const
{
  if (this->length() <= rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector3<T>::operator>=(const Vector3<T>& rhs) const
{
  if (this->length() >= rhs.length())
    return true;
  else
    return false;
}

template <typename T>
Vector3<T>	operator+(const Vector3<T>& lhs)
{
  return lhs;
}

template <typename T>
Vector3<T>	operator-(const Vector3<T>& lhs)
{
  Vector3<T>	ret;
  
  ret.x = -lhs.x;
  ret.y = -lhs.y;
  ret.z = -lhs.z;
  return ret;
}


template <typename T>
Vector3<T>	operator-(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x - rhs.x;
  ret.y = lhs.y - rhs.y;
  ret.z = lhs.z - rhs.z;
  return ret;
}

template <typename T>
Vector3<T>	operator*(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x * rhs.x;
  ret.y = lhs.y * rhs.y;
  ret.z = lhs.z * rhs.z;
  return ret;
}

template <typename T>
Vector3<T>	operator/(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x / rhs.x;
  ret.y = lhs.y / rhs.y;
  ret.z = lhs.z / rhs.z;
  return ret;
}

template <typename T>
Vector3<T>	operator%(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x % rhs.x;
  ret.y = lhs.y % rhs.y;
  ret.z = lhs.z % rhs.z;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator+(const Vector3<T>& lhs, const U& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x + rhs;
  ret.y = lhs.y + rhs;
  ret.z = lhs.z + rhs;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator-(const Vector3<T>& lhs, const U& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x - rhs;
  ret.y = lhs.y - rhs;
  ret.z = lhs.z - rhs;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator*(const Vector3<T>& lhs, const U& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x * rhs;
  ret.y = lhs.y * rhs;
  ret.z = lhs.z * rhs;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator/(const Vector3<T>& lhs, const U& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x / rhs;
  ret.y = lhs.y / rhs;
  ret.z = lhs.z / rhs;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator%(const Vector3<T>& lhs, const U& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs.x % rhs;
  ret.y = lhs.y % rhs;
  ret.z = lhs.z % rhs;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator+(const U& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs + rhs.x;
  ret.y = lhs + rhs.y;
  ret.z = lhs + rhs.z;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator-(const U& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs - rhs.x;
  ret.y = lhs - rhs.y;
  ret.z = lhs - rhs.z;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator*(const U& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs * rhs.x;
  ret.y = lhs * rhs.y;
  ret.z = lhs * rhs.z;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator/(const U& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs / rhs.x;
  ret.y = lhs / rhs.y;
  ret.z = lhs / rhs.z;
  return ret;
}

template <typename T, typename U>
Vector3<T>	operator%(const U& lhs, const Vector3<T>& rhs)
{
  Vector3<T>	ret;
  
  ret.x = lhs % rhs.x;
  ret.y = lhs % rhs.y;
  ret.z = lhs % rhs.z;
  return ret;
}

template <typename T>
Vector3<T>::operator bool() const
{
  return (this->x || this->y || this->z);
}

template <typename T>
std::ostream&	operator<<(std::ostream& os, const Vector3<T>& rhs)
{
  os << "Vector3 { " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";
  return os;
}

template <typename T>
Vector2<T>::Vector2(T x, T y)
  : x(x),
    y(y)
{
}

template <typename T>
template<typename U>
Vector2<T>::Vector2(const Vector2<U>& rhs)
  : x(rhs.x),
    y(rhs.y)
{
}

template <typename T>
Vector2<T>::~Vector2()
{
}

template <typename T>
void		Vector2<T>::normalize()
{
  T		div;

  div = this->length();
  this->x /= div;
  this->y /= div;
}

template <typename T>
T		Vector2<T>::length() const
{
  T		ret;

  ret = this->x * this->x + this->y * this->y;
  ret = sqrt(ret);
  return ret;
}

template <typename T>
const T*		Vector2<T>::toArray() const
{
  return reinterpret_cast<const T*>(this);
}

template <typename T>
Vector2<T>&	Vector2<T>::operator=(const Vector2<T>& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  return *this;
}

template <typename T>
Vector2<T>&	Vector2<T>::operator+=(const Vector2<T>& rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

template <typename T>
Vector2<T>&	Vector2<T>::operator-=(const Vector2<T>& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  return *this;
}

template <typename T>
Vector2<T>&	Vector2<T>::operator*=(const Vector2<T>& rhs)
{
  this->x *= rhs.x;
  this->y *= rhs.y;
  return *this;
}

template <typename T>
Vector2<T>&	Vector2<T>::operator/=(const Vector2<T>& rhs)
{
  this->x /= rhs.x;
  this->y /= rhs.y;
  return *this;
}

template <typename T>
Vector2<T>&	Vector2<T>::operator%=(const Vector2<T>& rhs)
{
  this->x %= rhs.x;
  this->y %= rhs.y;
  return *this;
}

template <typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator+=(const U& rhs)
{
  this->x += rhs;
  this->y += rhs;
  return *this;
}

template <typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator-=(const U& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  return *this;
}

template <typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator*=(const U& rhs)
{
  this->x *= rhs;
  this->y *= rhs;
  return *this;
}

template <typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator/=(const U& rhs)
{
  this->x /= rhs;
  this->y /= rhs;
  return (*this);
}

template <typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator%=(const U& rhs)
{
  this->x %= rhs;
  this->y %= rhs;
  return (*this);
}

template<typename T>
template<typename U>
Vector2<T>&	Vector2<T>::operator=(const U& rhs)
{
  this->x = rhs;
  this->y = rhs;
  return (*this);
}

template <typename T>
bool		Vector2<T>::operator==(const Vector2<T>& rhs) const
{
  if (this->x == rhs.x && this->y == rhs.y)
    return true;
  else
    return false;
}

template <typename T>
bool		Vector2<T>::operator!=(const Vector2<T>& rhs) const
{
  if (this->x != rhs.x || this->y != rhs.y)
    return true;
  else
    return false;
}

template <typename T>
bool		Vector2<T>::operator<(const Vector2<T>& rhs) const
{
  if (this->length() < rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector2<T>::operator>(const Vector2<T>& rhs) const
{
  if (this->length() > rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector2<T>::operator<=(const Vector2<T>& rhs) const
{
  if (this->length() <= rhs.length())
    return true;
  else
    return false;
}

template <typename T>
bool		Vector2<T>::operator>=(const Vector2<T>& rhs) const
{
  if (this->length() >= rhs.length())
    return true;
  else
    return false;
}

template <typename T>
Vector2<T>	operator+(const Vector2<T>& lhs)
{
  return lhs;
}

template <typename T>
Vector2<T>	operator-(const Vector2<T>& lhs)
{
  Vector2<T>	ret;
  
  ret.x = -lhs.x;
  ret.y = -lhs.y;
  return ret;
}

template <typename T>
Vector2<T>	operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x + rhs.x;
  ret.y = lhs.y + rhs.y;
  return ret;
}

template <typename T>
Vector2<T>	operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x - rhs.x;
  ret.y = lhs.y - rhs.y;
  return ret;
}

template <typename T>
Vector2<T>	operator*(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x * rhs.x;
  ret.y = lhs.y * rhs.y;
  return ret;
}

template <typename T>
Vector2<T>	operator/(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x / rhs.x;
  ret.y = lhs.y / rhs.y;
  return ret;
}

template <typename T>
Vector2<T>	operator%(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x % rhs.x;
  ret.y = lhs.y % rhs.y;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator+(const Vector2<T>& lhs, const U& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x + rhs;
  ret.y = lhs.y + rhs;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator-(const Vector2<T>& lhs, const U& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x - rhs;
  ret.y = lhs.y - rhs;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator*(const Vector2<T>& lhs, const U& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x * rhs;
  ret.y = lhs.y * rhs;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator/(const Vector2<T>& lhs, const U& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x / rhs;
  ret.y = lhs.y / rhs;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator%(const Vector2<T>& lhs, const U& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs.x % rhs;
  ret.y = lhs.y % rhs;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator+(const U& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs + rhs.x;
  ret.y = lhs + rhs.y;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator-(const U& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs - rhs.x;
  ret.y = lhs - rhs.y;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator*(const U& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs * rhs.x;
  ret.y = lhs * rhs.y;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator/(const U& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs / rhs.x;
  ret.y = lhs / rhs.y;
  return ret;
}

template <typename T, typename U>
Vector2<T>	operator%(const U& lhs, const Vector2<T>& rhs)
{
  Vector2<T>	ret;
  
  ret.x = lhs % rhs.x;
  ret.y = lhs % rhs.y;
  return ret;
}

template <typename T>
std::ostream&	operator<<(std::ostream& os, const Vector2<T>& rhs)
{
  os << "Vector2 { " << rhs.x << ", " << rhs.y << " }";
  return os;
}

}
#endif	//__VECTOR_HPP__
