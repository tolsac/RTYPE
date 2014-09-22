/*
** Authentificate.hpp for Authentificate in /home/tolsa/rtype-2015-tolsa_c/rtype-client
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Fri Jan 18 00:36:27 2013 tolsa_c
** Last update Fri Jan 18 00:57:53 2013 tolsa_c
*/

#ifndef AUTHENTIFICATE_HPP_
# define AUTHENTIFICATE_HPP_

#include <fstream>

class Authentificate
{
public:
  Authentificate()
  {
    this->_login = "player";
    this->_ip = "127.0.0.1";
    this->_port = 4242;
    this->_valid = true;
  }

  ~Authentificate(){}
  
  std::string		getLogin() const
  {
    return _login;
  }

  std::string		getIp() const
  {
    return _ip;
  }
  
  int			getPort() const
  {
    return _port;
  }
  
  bool			isValid() const
  {
    return _valid;
  }
  
  void			load()
  {
    std::ifstream	f;
    char		buff[256] = {0};
    
    f.open("connexion_infos.txt");
    if (!f)
      {
	this->_valid = false;
	return;
      }
    f >> this->_login;
    f >> this->_ip;
    f >> this->_port;
    f.close();
  }

private:
  std::string		_login;
  std::string		_ip;
  int			_port;
  bool			_valid;
};

#endif /* !AUTHENTIFICATE_HPP_ */
