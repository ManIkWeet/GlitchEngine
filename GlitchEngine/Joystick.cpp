#include "Joystick.h"
#include "Logger.h"

Joystick::Joystick(IDirectInput8* argInterface, HWND hDlg)
{
	Logger::GetInstance().Log(LogLevel::WARNING, "Todo: Implement joystick correctly");
	available = false;
	return;
	HRESULT result;

	//Initialize the direct input interface for the joystick.
	result = argInterface->CreateDevice(GUID_Joystick, &joystick, NULL);
	if (FAILED(result))
	{
		Logger::GetInstance().Log(INFO, "There is no joystick!");
		return;
	}

	//Set the data format.  In this case since it is a joystick we can use the predefined data format.
	result = joystick->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(result))
	{
		return;
	}

	//Set the cooperative level of the joystick to not share with other programs.
	result = joystick->SetCooperativeLevel(hDlg, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return;
	}

	//Now acquire the joystick.
	result = joystick->Acquire();
	if (FAILED(result))
	{
		return;
	}

	joystickListeners = std::vector<JoystickListener*>();
	available = true;
};

Joystick::~Joystick()
{
	delete joystick;
};

void Joystick::AddJoystickListener(JoystickListener* argJoystickListener)
{
	joystickListeners.push_back(argJoystickListener);
};

bool Joystick::DoInput()
{
	HRESULT result;

	// Read the joystick device.
	result = joystick->GetDeviceState(sizeof(DIJOYSTATE2), &joystickState);
	if (FAILED(result))
	{
		// If the joystick lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			joystick->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
};

/*void Joystick::processInput()
{
	bool update = false;
	if (joystickStateOld.lARx != joystickState.lARx || joystickStateOld.lARy != joystickState.lARy || joystickStateOld.lARz != joystickState.lARz ||
		joystickStateOld.lAX != joystickState.lAX || joystickStateOld.lAY != joystickState.lAY || joystickStateOld.lAZ != joystickState.lAZ ||
		joystickStateOld.lFRx != joystickState.lFRx || joystickStateOld.lFRy != joystickState.lFRy || joystickStateOld.lFRz != joystickState.lFRz ||
		joystickStateOld.lFX != joystickState.lFX || joystickStateOld.lFY != joystickState.lFY || joystickStateOld.lFZ != joystickState.lFZ ||
		joystickStateOld.lRx != joystickState.lRx || joystickStateOld.lRy != joystickState.lRy || joystickStateOld.lRz != joystickState.lRz ||
		joystickStateOld.lVRx != joystickState.lVRx || joystickStateOld.lVRy != joystickState.lVRy || joystickStateOld.lVRz != joystickState.lVRz ||
		joystickStateOld.lVX != joystickState.lVX || joystickStateOld.lVY != joystickState.lVY || joystickStateOld.lVZ != joystickState.lVZ ||
		joystickStateOld.lX != joystickState.lX || joystickStateOld.lY != joystickState.lY || joystickStateOld.lZ != joystickState.lZ)
	{
		update = true;
	}
	if (!update)
	{
		for (int i = 0; i < 128; i++)
		{
			if (joystickStateOld.rgbButtons[i] != joystickState.rgbButtons[i])
			{
				update = true;
				break;
			}
		}
	}

	if (!update)
	{
		for (int i = 0; i < 4; i++)
		{
			if (joystickStateOld.rgdwPOV[i] != joystickState.rgdwPOV[i])
			{
				update = true;
				break;
			}
		}
	}
	if (!update)
	{
		for (int i = 0; i < 2; i++)
		{
			if (joystickStateOld.rglASlider[i] != joystickState.rglASlider[i])
			{
				update = true;
				break;
			}
		}
	}

	if (!update)
	{
		for (int i = 0; i < 2; i++)
		{
			if (joystickStateOld.rglSlider[i] != joystickState.rglSlider[i])
			{
				update = true;
				break;
			}
		}
	}
	if (!update)
	{
		for (int i = 0; i < 2; i++)
		{
			if (joystickStateOld.rglFSlider[i] != joystickState.rglFSlider[i])
			{
				update = true;
				break;
			}
		}
	}
	if (!update)
	{
		for (int i = 0; i < 2; i++)
		{
			if (joystickStateOld.rglVSlider[i] != joystickState.rglVSlider[i])
			{
				update = true;
				break;
			}
		}
	}
	if (update)
	{
		updateListeners();
		joystickStateOld = joystickState;
	}
};

void Joystick::updateListeners()
{
	for each (JoystickListener* current in joystickListeners)
	{
		current->useJoystickInput(joystickState);
	}
};*/