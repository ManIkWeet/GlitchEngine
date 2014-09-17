#include "InputPrinter.h"
#include "Logger.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string> 

InputPrinter::InputPrinter()
{
}


InputPrinter::~InputPrinter()
{
}

void InputPrinter::KeyPressed(KeyEvent ke)
{
	std::ostringstream oss;
	oss << "Pressed key: " << ke.theKey;
	Logger::GetInstance().Log(LogLevel::INFO, oss.str());
}

void InputPrinter::KeyReleased(KeyEvent ke)
{
	std::ostringstream oss;
	oss << "Released key: " << ke.theKey;
	Logger::GetInstance().Log(LogLevel::INFO, oss.str());
}

void InputPrinter::MouseMoved(MouseEvent me)
{
	std::ostringstream oss;
	oss << "The mouse has moved: " << me.mouseDifferenceX << "X, " << me.mouseDifferenceY << "Y, " << me.mouseDifferenceZ << "Z";
	Logger::GetInstance().Log(LogLevel::INFO, oss.str());
}

void InputPrinter::MousePressed(MouseEvent me)
{
	std::ostringstream oss;
	oss << "Pressed mouse button: " << me.mouseButton;
	Logger::GetInstance().Log(LogLevel::INFO, oss.str());
}

void InputPrinter::MouseReleased(MouseEvent me)
{
	std::ostringstream oss;
	oss << "Released mouse button: " << me.mouseButton;
	Logger::GetInstance().Log(LogLevel::INFO, oss.str());
}