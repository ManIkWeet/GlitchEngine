/*!
3D Engine
Joystick.h
Purpose: Reads, processes and uses joystick input and updates the joysticklisteners accordingly.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "windows.h"
#include "Dinput.h"
#include "JoystickListener.h"
#include <vector>
#include <array>

class Joystick
{
public:
	/*!
	Uses directInput to set the joystick.

	@param directInput: Pointer to the directInput, which is used to create the joystick.
	@param hwnd: The hwnd of the window that will catch the joystick input.
	*/
	Joystick(IDirectInput8* argInterface, HWND hDlg);
	~Joystick();

	/*!
	Adds a joysticklistener to a list of joysticklisteners.

	@param argJoystickListener: A pointer to the joysticklistener which is to be added.
	*/
	void AddJoystickListener(JoystickListener* argJoystickListener);

	/*!
	Does everything needed to get any joystick input to the listeners.
	*/
	bool DoInput();

	bool available;

private:
	IDirectInputDevice8* joystick;
	DIJOYSTATE2 joystickState;
	DIJOYSTATE2 joystickStateOld;
	std::vector<JoystickListener*> joystickListeners;
};
#endif