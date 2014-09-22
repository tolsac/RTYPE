//
// Convert.hh for generic in /home/petit_c//projets/c++/plazza/plazza-2015-d-eima_g
// 
// Made by clement petit
// Login   <petit_c@epitech.net>
// 
// Started on  Wed Apr 11 13:01:28 2012 clement petit
// Last update Wed May 16 11:31:17 2012 clement petit
//

#ifndef		__CONVER_HH__
#define		__CONVER_HH__

#include	<sstream>

namespace epi
{
  template<typename T>
  T		fromString(const std::string& buff)
  {
    std::stringstream	ss;
    T			val;
    
    ss << buff;
    ss >> val;
    return (val);
  }
  
  template<typename T>
  std::string	toString(T val)
  {
    std::stringstream	ss;
    std::string		buff;

    ss << val;
    ss >> buff;
    return (buff);
  }
  
}

#endif		//__CONVER_HH__
