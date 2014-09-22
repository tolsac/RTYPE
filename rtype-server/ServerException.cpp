/* Auteur: Bertrand Boyer */
/* Commenc� le 12/01/13. */
/* Derni�re modification: 12/01/13. */

#include <ServerException.h>

ServerException::ServerException(void)
{
	this->error.assign("Une erreur est survenue !");
}

ServerException::ServerException(const char *msg)
{
	this->error.assign(msg);
}

ServerException::~ServerException(void) throw()
{
}

const char		*ServerException::what() const throw()
{
	return (this->error.c_str());
}
