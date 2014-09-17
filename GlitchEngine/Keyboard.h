/*!
GlitchEngine
Keyboard.h
Purpose: Reads, processes and uses keyboard input and updates the keyboardlisteners accordingly.

@author Robert
@version 1.0
*/

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "windows.h"
#include "Dinput.h"
#include "KeyboardListener.h"
#include <vector>
#include <array>

class Keyboard
{
public:
	/*!
	Uses directInput to set the keyboard.

	@param directInput: Pointer to the directInput, which is used to create the keyboard.
	@param hwnd: The hwnd of the window that will catch the keyboard input.
	*/
	Keyboard(IDirectInput8* directInput, HWND hwnd);
	~Keyboard();

	/*!
	Adds a keyboardlistener to a list of keyboardlisteners.

	@param argKeyboardListener: A pointer to the keyboardlistener which is to be added.
	*/
	void AddKeyboardListener(KeyboardListener* argKeyboardListener);

	/*!
	Does everything needed to get any keyboard input to the listeners.
	*/
	bool DoInput();

private:
	IDirectInputDevice8* keyboard;
	std::array<unsigned char, 256> keyboardStateOld;
	std::vector<KeyboardListener*> keyboardListeners;
};
#endif