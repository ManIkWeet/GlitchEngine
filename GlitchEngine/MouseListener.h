/*!
3D Engine
MouseListener.h
Purpose: Interface to unify the way mouse input is used.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _MOUSELISTENER_H_
#define _MOUSELISTENER_H_

#include "dinput.h"
#include "MouseEvent.h"

class MouseListener
{
public:
	MouseListener();
	virtual ~MouseListener();

	/*!
	Abstract method which needs to be implemented with actions based on mouse input.
	*/
	virtual void MouseMoved(MouseEvent me) = 0;
	virtual void MousePressed(MouseEvent me) = 0;
	virtual void MouseReleased(MouseEvent me) = 0;
};
#endif