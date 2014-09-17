#include "InputManager.h"
#include "Keyboard.h"
#include "Logger.h"
#include "Defines.h"

InputManager::InputManager()
{
	directInput = NULL;
	myKeyboard = NULL;
	myMouse = NULL;
	myJoystick = NULL;
};

InputManager::~InputManager()
{
	// Release the mouse.
	myMouse->~Mouse();

	// Release the keyboard.
	myKeyboard->~Keyboard();

	// Release the joystick.
	myJoystick->~Joystick();

	// Release the main interface to direct input.
	if (directInput)
	{
		directInput->Release();
		directInput = 0;
	}
};

bool InputManager::initialize(HWND hwnd)
{
	HRESULT result;

	// Initialize the main direct input interface.
	result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	myKeyboard = new Keyboard(directInput, hwnd);
	myMouse = new Mouse(directInput, hwnd);
	myJoystick = new Joystick(directInput, hwnd);

	UpdateAll();//update all of them once to make sure they get a correct state before being able to send anything to their listeners...

	return true;
};

void InputManager::UpdateAll()
{
	// Read the current state of the joystick.
	if (myJoystick->available)
	{
		if (!myJoystick->DoInput())
		{
			//return false;
		}
	}

	// Read the current state of the keyboard.
	if (!myKeyboard->DoInput())
	{
		//return false;
	}

	// Read the current state of the mouse.
	if (!myMouse->DoInput())
	{
		//return false;
	}
	//return true;
};

void InputManager::AddListenerToKeyboard(KeyboardListener* argKeyboardListener)
{
	myKeyboard->AddKeyboardListener(argKeyboardListener);
}

void InputManager::AddListenerToMouse(MouseListener* argMouseListener)
{
	myMouse->AddMouseListener(argMouseListener);
}

void InputManager::AddListenerToJoystick(JoystickListener* argJoystickListener)
{
	myJoystick->AddJoystickListener(argJoystickListener);
}