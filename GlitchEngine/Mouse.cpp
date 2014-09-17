#include "Mouse.h"
#include <array>

Mouse::Mouse(IDirectInput8* directInput, HWND hwnd)
{
	mouseListeners = std::vector<MouseListener*>();

	HRESULT result;

	// Store the screen size which will be used for positioning the mouse cursor.
	//screenWidth = argScreenWidth;
	//screenHeight = argScreenHeight;

	// Initialize the location of the mouse on the screen.
	oldMouseState = { 0, 0, 0, { 0, 0, 0, 0 } };

	// Initialize the direct input interface for the mouse.
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if (FAILED(result))
	{
		return;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return;
	}

	// Acquire the mouse.
	result = mouse->Acquire();
	if (FAILED(result))
	{
		return;
	}
};

Mouse::~Mouse()
{
	if (mouse)
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = 0;
	}
};

void Mouse::AddMouseListener(MouseListener* argMouseListener)
{
	mouseListeners.push_back(argMouseListener);
};

bool Mouse::DoInput()
{
	HRESULT result;
	DIMOUSESTATE mouseState;

	// Read the mouse device.
	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse->Acquire();
			return false;
		}
		else
		{
			return false;
		}
	}

	//Process mouse buttons first, that way the listener can prepare for a potential dragging movement.
	int supportedMouseKeys = 4;
	for (int i = 0; i < supportedMouseKeys; ++i)
	{
		if (oldMouseState.rgbButtons[i] != mouseState.rgbButtons[i])
		{
			if (mouseState.rgbButtons[i] & 0x80)
			{
				for each (MouseListener* current in mouseListeners)
				{
					MouseEvent me = { 0, 0, 0, i };
					current->MousePressed(me);//Don't give relative movement, dragging with 3 buttons would give 3 times the relative movement...
				}
			}
			else
			{
				for each (MouseListener* current in mouseListeners)
				{
					MouseEvent me = { 0, 0, 0, i };//Don't give relative movement, dragging with 3 buttons would give 3 times the relative movement...
					current->MouseReleased(me);
				}
			}
		}
	}

	if (mouseState.lX != oldMouseState.lX || mouseState.lY != oldMouseState.lY || mouseState.lZ != oldMouseState.lZ)
	{
		for each (MouseListener* current in mouseListeners)
		{
			MouseEvent me = { mouseState.lX, mouseState.lY, mouseState.lZ, -1 };
			current->MouseMoved(me);
		}
	}
	oldMouseState = mouseState;

	return true;
};