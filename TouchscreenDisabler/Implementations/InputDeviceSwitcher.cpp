#include <Implementations/InputDeviceSwitcher.hpp>

void InputDeviceSwitcher::SwitchDevice(int deviceId, bool turnOn)
{
	// Getting display pointer
	auto displayGetter = new DisplayGetter();
	auto displayPtr = displayGetter->GetDisplay();

	auto deviceEnabledPropertyAtom = XInternAtom(displayPtr, DeviceEnabledPropertyName.toLocal8Bit().data(), true);

	unsigned char propertyValue = 0;
	if (turnOn)
	{
		propertyValue = 1;
	}

	// Setting property
	XIChangeProperty(displayPtr,
				deviceId,
				deviceEnabledPropertyAtom,
				XA_INTEGER,
				8, // Is Enabled is 8-bit property
				PropModeReplace, // Replacing property
				&propertyValue,
				1); // Property is 1 byte

	// Freeing stuff
	displayGetter->FreeDisplay(displayPtr);
	SafeDelete(displayGetter);
}
