#include "FileManager.h"
//#include	"Platform.h"
//#ifdef	PLATFORM_WIN32
//	#include <direct.h>
//#endif

#include <fstream>

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

enum LoadState
{
	ATTRIBUTES,
	CONTENTS
};

int state;

bool FileManager::LoadContent(const char *filename, 
			std::vector<std::vector<std::string> > &attributes,
			std::vector<std::vector<std::string> > &contents)
{
	std::ifstream openfile(filename);
	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			std::string line;
			std::getline(openfile, line);
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			if (line.find("Load=") != std::string::npos)
			{
				state = ATTRIBUTES;
				line.erase(0, line.find('=') + 1);
				tempAttributes.clear();
			}
			else
			{
				state = CONTENTS;
				tempContents.clear();
			}
			line.erase(std::remove(line.begin(), line.end(), '['), line.end());
			std::stringstream str(line);
			while (str)
			{
				std::getline(str, line, ']');
				if (line != "")
				{
					if (state == ATTRIBUTES)
					{
						
						tempAttributes.push_back(line);
					}
					else
					{
						
						tempContents.push_back(line);
					}
				}
			}
			if (state == CONTENTS && tempContents.size() > 0)
			{
				attributes.push_back(tempAttributes);
				contents.push_back(tempContents);
			}
		}
	}
	else
	{
		std::cout << "Couldn't find PreLoad file" << std::endl;
		return (false);
	}
	return (true);
}
