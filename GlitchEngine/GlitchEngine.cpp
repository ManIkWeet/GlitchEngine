// GlitchEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "InputPrinter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Logger::GetInstance().Log(LogLevel::INFO, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::DEBUG, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::WARNING, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::CRITICAL, "Logger is working!");
	Logger::GetInstance().Log(LogLevel::NONE, "Logger is working!");

	WindowManager* wm = new WindowManager();
	wm->NewWindow(10, 10, 1280, 720);

	InputManager* im = new InputManager();
	im->initialize(wm->GetLastWindow()->GetHWND());

	InputPrinter* tim = new InputPrinter();
	im->AddListenerToKeyboard(tim);
	im->AddListenerToMouse(tim);


	while (wm->HasActiveWindow())
	{
		wm->UpdateWindows();
		im->UpdateAll();
	}

	return 0;
}