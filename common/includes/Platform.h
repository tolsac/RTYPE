/* Header de definition des plateformes pour la portabilite. */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* Linux */
#if defined linux || defined __linux__ || defined __linux
	#define PLATFORM_LINUX
	#define PLATFORM_NAME "Linux"
#endif

/* Windows */
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	#define PLATFORM_WIN32
	#define PLATFORM_NAME "Windows"
#endif

#endif //! _PLATFORM_H_
