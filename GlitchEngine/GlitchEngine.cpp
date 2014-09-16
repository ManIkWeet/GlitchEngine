// GlitchEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include "WindowManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger::GetInstance().Log(LogLevel::INFO, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::DEBUG, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::WARNING, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::CRITICAL, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::NONE, "Logger is working!");

	WindowManager* wm = new WindowManager();

	wm->NewWindow(10, 10, 1280, 720);

	while (wm->HasActiveWindow())
	{
		wm->UpdateWindows();
	}

	return 0;
}

