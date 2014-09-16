#include <windows.h>
#include "Window.h"
/*#include "Logger.h"
#include "LoggerPool.h"*/

Window::Window(/*Renderer::Renderer* renderer*/)
{
	//Set the default data for the window class.
	//These can be reset in the derived class's constructor.
	_WndClass.cbSize = sizeof(_WndClass);
	_WndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;;
	_WndClass.lpfnWndProc = BaseWndProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = NULL;
	_WndClass.hIcon = NULL;
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	_WndClass.lpszMenuName = NULL;
	_WndClass.hIconSm = NULL;

	_dwExtendedStyle = NULL;
	_dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_pszClassName = L"Window";
	_pszTitle = L"You should not be reading this default title, it only takes time!";
	state = normal;
};

Window::~Window()
{
	Logger::GetInstance().Log(LogLevel::WARNING, "Todo: Proper Window deconstructor");
	//delete _hwnd;
};

void Window::SetTitle(char* title)
{
	size_t origsize = strlen(title) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, title, _TRUNCATE);

	_pszTitle = wcstring;
	SetWindowText(_hwnd, wcstring);

	//	delete[] wcstring;
}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		render(/*NULL*/);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		state = closed;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		Resize();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
};

void Window::Resize()
{
	RECT rect;
	if (GetWindowRect(_hwnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		//renderer->setRenderSize(width, height);
	}
};

void Window::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
};

HWND Window::Create(int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance)
{
	_WndClass.lpszClassName = _pszClassName;
	_WndClass.hInstance = hInstance;

	//If we're already registered, this call will fail.
	RegisterClassEx(&_WndClass);

	_hwnd = CreateWindowEx(_dwExtendedStyle, _pszClassName, _pszTitle, _dwStyle, x, y, nWidth, nHeight, hParent, hMenu, hInstance, (void*)this);
	state = normal;
	return _hwnd;
};

LRESULT CALLBACK Window::BaseWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//A pointer to the object is passed in the CREATESTRUCT
	if (msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA,
			(LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
	}

	//Retrieve the pointer
	Window *pObj = (Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	//Filter message through child classes
	if (pObj)
	{
		return pObj->WindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
};

void Window::render(/*Scene::Scene *scene*/)
{
	/*if (scene)
	{
		//scene->updateEntities();
	}*/
	RECT rect;
	HDC hDC = GetDC(_hwnd);
	PAINTSTRUCT PaintStruct;
	BeginPaint(_hwnd, &PaintStruct);
	GetClientRect(_hwnd, &rect);
	DrawText(hDC, L"Hello, screen that is damn hard to get!", 39, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndPaint(_hwnd, &PaintStruct);
	ReleaseDC(_hwnd, hDC);
	//renderer->Render(_hwnd, scene);
};

HWND Window::GetHWND()
{
	return _hwnd;
}

WindowState Window::GetWindowState()
{
	return state;
}