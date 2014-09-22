/* Classes d'exception pour le serveur. */
/* Auteur: Bertrand Boyer */
/* Commencé le 12/01/13. */
/* Dernière modification: 12/01/13. */

#ifndef __SERVEREXCEPTION_H__
#define __SERVEREXCEPTION_H__

#include <exception>
#include <string>

#include <GlobalServerIncludes.h>

/* Classe d'exception de base du serveur. */
class ServerException : public std::exception
{
private:
	std::string		error;

public:
	ServerException(void);
	ServerException(const char* msg);
	virtual ~ServerException(void) throw();

	virtual const char		*what() const  throw();
};

#endif /* __SERVEREXCEPTION_H__ */
