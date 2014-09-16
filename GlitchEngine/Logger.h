/*!
GlitchEngine
Logger.h
Purpose: Used to log info, warnings and errors to the command line and the log-file.

@author Robert
@version 1.0
*/

#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <fstream>
#include <windows.h>

enum LogLevel { INFO, DEBUG, WARNING, CRITICAL, NONE  };

class Logger
{
public:

	/*!
	Returns the singleton logger.
	*/
	static Logger& GetInstance()
	{
		static Logger instance;
		return instance;
	}

	/*!
	Method that logs a type and message.
	*/
	void Log(LogLevel type, std::string message);
private:
	Logger()
	{
		//Constructor, don't implement
	}

	Logger(Logger const&); //Don't implement
	void operator=(Logger const&); //Don't implement

	std::ofstream logfile;

	enum Colors 
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		cyan = 11,
		red = 12,
		purple = 13,
		yellow = 14,
		white = 15
	};

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);;
};
#endif