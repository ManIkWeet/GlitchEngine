#include "WindowManager.h"
#include <string>
#include "Logger.h"
#include <sstream>

WindowManager::WindowManager(/*SceneManager *sManager*/)
{
	//sceneManager = sManager;
};

WindowManager::~WindowManager()
{
	while (!windows.empty())
	{
		delete windows.back(), windows.pop_back();
	}
	/*while (!windowListeners.empty())
	{
	delete windowListeners.back(), windowListeners.pop_back();
	}
	delete sceneManager;*/
};

HWND WindowManager::NewWindow(/*Renderer *renderer, */int x, int y, int width, int height)
{
	Window *window = new Window(/*renderer*/);
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		Logger::GetInstance().Log(CRITICAL, "Could not make window!");
		delete window;
	}
	else
	{
		windows.push_back(window);
	}

	return hwnd;
};

void WindowManager::UpdateWindows()
{
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0U, 0U, true) > 0)//if there's more than one message, go through all of them.
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	for (long index = 0; index < (long)windows.size(); ++index) {
		windows.at(index)->render(/*NULL*/);// Todo: get the scene that has to be rendered in this window...
	}
};

bool WindowManager::HasActiveWindow()
{
	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end();) { // note the missing ++iter !

		if ((*it)->GetWindowState() == closed)
		{
			//delete window
			delete * it;
			it = windows.erase(it);
		}
		else {
			++it;
		}
	}

	if (windows.size() != 0)
	{
		return true;
	}
	return false;
};

Window* WindowManager::GetLastWindow()
{
	return windows.back();
}

Window* WindowManager::GetWindowByHWND(HWND hwnd)
{
	for (std::vector<Window*>::iterator it = windows.begin(); it != windows.end(); ++it) {

		if ((*it)->GetHWND() == hwnd)
		{
			return *it;
		}
	}

	return NULL;
}

std::vector<Window*>* WindowManager::GetAllWindows()
{
	return &windows;
}