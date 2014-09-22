#include <Logger.h>

Logger::Logger(void)
{
}

Logger::~Logger(void)
{
}

char*			Logger::makeDate()
{
	time_t		rawTime;
	char		*date = new char[SIZE_DATE];

	rawTime = time(&rawTime);
#ifdef PLATFORM_WIN32
	ctime_s(date, SIZE_DATE - 1, &rawTime);
#endif
#ifdef PLATFORM_LINUX
	date = ctime_r(&rawTime, date);
#endif
	date[strlen(date) - 1] = '\0';
	return (date);
}

void			Logger::logInfo(const std::string& msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cout << "INFO: " << date << " : " << msg.c_str() << std::endl;
	delete[] (date);
}

void			Logger::logInfo(const char *msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cout << "INFO: " << date << " : " << msg << std::endl;
	delete[] (date);
}

void			Logger::logInfo(const std::ostringstream& msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cout << "INFO: " << date << " : " << msg.str() << std::endl;
	delete[] (date);
}

void			Logger::logDebug(const std::string& msg)
{
#ifdef DEBUG
	char		*date = NULL;

	date = makeDate();
	std::cout << "DEBUG: " << date << " : " << msg.c_str() << std::endl;
	delete[] (date);
#endif
}

void			Logger::logDebug(const char *msg)
{
#ifdef DEBUG
	char		*date = NULL;

	date = makeDate();
	std::cout << "DEBUG: " << date << " : " << msg << std::endl;
	delete[] (date);
#endif
}

void			Logger::logDebug(const std::ostringstream& msg)
{
#ifdef DEBUG
	char		*date = NULL;

	date = makeDate();
	std::cout << "DEBUG: " << date << " : " << msg.str() << std::endl;
	delete[] (date);
#endif
}

void			Logger::logError(const std::string& msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cerr << "ERROR: " << date << " : " << msg.c_str() << std::endl;
	delete[] (date);
}

void			Logger::logError(const char *msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cerr << "ERROR: " << date << " : " << msg << std::endl;
	delete[] (date);
}

void			Logger::logError(const std::ostringstream& msg)
{
	char		*date = NULL;

	date = makeDate();
	std::cout << "ERROR: " << date << " : " << msg.str() << std::endl;
	delete[] (date);
}
