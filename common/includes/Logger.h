/* Header de la classe Logger. */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <sstream>
#include <ctime>

#include <string.h>

#include <Platform.h>

class Logger
{
private:
	static const int	SIZE_DATE = 32; /* Ne doit jamais être inférieur à 27 ! */

private:
	static char			*makeDate();

public:
	Logger(void);
	~Logger(void);

	/* Log d'infos.*/
	static void			logInfo(const std::string& msg);
	static void			logInfo(const char *msg);
	static void			logInfo(const std::ostringstream& msg);

	/* Log de debug.*/
	static void			logDebug(const std::string& msg);
	static void			logDebug(const char *msg);
	static void			logDebug(const std::ostringstream& msg);

	/* Log d'erreur.*/
	static void			logError(const std::string& msg);
	static void			logError(const char *msg);
	static void			logError(const std::ostringstream& msg);
};

#endif //! __LOGGER_H__
