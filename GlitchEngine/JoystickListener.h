/*!
3D Engine
JoystickListener.h
Purpose: Interface to unify the way joystick input is used.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _JOYSTICKLISTENER_H_
#define _JOYSTICKLISTENER_H_

#include <array>
#include <dinput.h>

class JoystickListener
{
public:
	JoystickListener();
	virtual ~JoystickListener();

	/*!
	Abstract method which needs to be implemented with actions based on joystick input.

	@param DIJOYSTATE2: Array that contains the state of all buttons on the joystick.
	*/
	virtual void useJoystickInput(DIJOYSTATE2) = 0;
};
#endif