#pragma warning(disable : 4996)

#include "Keyboard.h"
#include "InputManager.h"
#include "Logger.h"

Keyboard::Keyboard(IDirectInput8* directInput, HWND hwnd)
{
	keyboardListeners = std::vector<KeyboardListener*>();

	HRESULT result;

	// Initialize the direct input interface for the keyboard.
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (FAILED(result))
	{
		return;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return;
	}

	// Now acquire the keyboard.
	result = keyboard->Acquire();
	if (FAILED(result))
	{
		return;
	}
};

Keyboard::~Keyboard()
{
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}
};

void Keyboard::AddKeyboardListener(KeyboardListener* argKeyboardListener)
{
	keyboardListeners.push_back(argKeyboardListener);
};

bool Keyboard::DoInput()
{
	HRESULT result;
	std::array<unsigned char, 256> keyboardState;

	// Read the keyboard device.
	result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
			return false;
		}
		else
		{
			return false;
		}
	}

	if (keyboardStateOld != keyboardState)
	{
		for (int i = 0; i < 256; ++i)
		{
			if (keyboardState[i] != keyboardStateOld[i])
			{
				if (keyboardState[i])
				{
					for each (KeyboardListener* current in keyboardListeners)
					{
						current->KeyPressed({ i });
					}
				}
				else
				{
					for each (KeyboardListener* current in keyboardListeners)
					{
						current->KeyReleased({ i });
					}
				}
			}
		}
	}
	std::copy(std::begin(keyboardState), std::end(keyboardState), std::begin(keyboardStateOld));

	return true;
};