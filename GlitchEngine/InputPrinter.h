#pragma once

#include "KeyboardListener.h"
#include "MouseListener.h"

class InputPrinter : public KeyboardListener, public MouseListener
{
public:
	InputPrinter();
	~InputPrinter();
	void KeyPressed(KeyEvent ke);
	void KeyReleased(KeyEvent ke);
	void MouseMoved(MouseEvent me);
	void MousePressed(MouseEvent me);
	void MouseReleased(MouseEvent me);
};

