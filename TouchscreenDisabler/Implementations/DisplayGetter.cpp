#include <Implementations/DisplayGetter.hpp>

Display* DisplayGetter::GetDisplay()
{
	return XOpenDisplay(NULL);
}

void DisplayGetter::FreeDisplay(Display* displayPtr)
{
	// Closing display
	XCloseDisplay(displayPtr);
}

