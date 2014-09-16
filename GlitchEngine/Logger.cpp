#include "Logger.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <sstream>
#include "Defines.h"

void Logger::Log(LogLevel type, std::string message)
{
	time_t t = time(0);   //get time now
	struct tm now;
	localtime_s(&now, &t); //convert timezone

	if (!logfile.is_open())
	{
		std::ostringstream oss;
		oss << "Logs\\Log " << now.tm_mday << "-" << (now.tm_mon + 1) << "-" << (now.tm_year + 1900) << ".txt";
		logfile.open(oss.str(), std::ios_base::app);
		if (!logfile.is_open())
		{
			throw(std::runtime_error("LOGGER: kan logbestand niet openen!"));
		}
	}
	
	std::ostringstream oss;

	SYSTEMTIME time;
	GetLocalTime(&time);

	char* logEntry = new char[16];
	sprintf_s(logEntry, 16, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	oss << logEntry;

	Colors color;
	switch (type)
	{
	case INFO:
		oss << "<INFO    >: ";
		color = Colors::white;
		break;
	case DEBUG:
		oss << "<DEBUG   >: ";
		color = Colors::cyan;
		break;
	case WARNING:
		oss << "<WARNING >: ";
		color = Colors::yellow;
		break;
	case CRITICAL:
		oss << "<CRITICAL>: ";
		color = Colors::red;
		break;
	default:
		oss << "<NONE    >: ";
		color = Colors::gray;
		break;
	}

	oss << message.c_str() << std::endl;

	logfile << oss.str();

	SetConsoleTextAttribute(consoleHandle, color);
	std::cout << oss.str();
};
