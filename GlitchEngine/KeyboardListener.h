/*!
3D Engine
KeyboardListener.h
Purpose: Interface to unify the way keyboard input is used.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _KEYBOARDLISTENER_H_
#define _KEYBOARDLISTENER_H_

#include <array>
#include "KeyEvent.h"

class KeyboardListener
{
public:
	KeyboardListener();
	virtual ~KeyboardListener();

	/*!
	Abstract method which needs to be implemented with actions based on keyboard input.

	@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	virtual void KeyPressed(KeyEvent ke) = 0;
	virtual void KeyReleased(KeyEvent ke) = 0;

};
#endif