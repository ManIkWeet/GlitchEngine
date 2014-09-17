/*!
3D Engine
Mouse.h
Purpose: Reads, processes and uses mouse input and updates the mouseListeners accordingly.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "dinput.h"
#include "MouseListener.h"
#include <vector>

class Mouse
{
public:
	/*!
	Uses directInput to set the mouse.

	@param directInput: Pointer to the directInput, which is used to create the mouse.
	@param hwnd: The hwnd of the window that will catch the mouse input.
	@param argScreenWidth: The width of the screen, so the mouse cursor can't leave the screen.
	@param argScreenHeight: The height of the screen, so the mouse cursor can't leave the screen.
	*/
	Mouse(IDirectInput8* directInput, HWND hwnd);
	~Mouse();

	/*!
	Adds a mouselistener to a list of mouselisteners.

	@param argMouseListener: A pointer to the mouselistener which is to be added.
	*/
	void AddMouseListener(MouseListener* argMouseListener);

	/*!
	Does everything needed to get any mouse input to the listeners.
	*/
	bool DoInput();

private:
	IDirectInputDevice8* mouse;
	DIMOUSESTATE oldMouseState;
	std::vector<MouseListener*> mouseListeners;
};
#endif