#include <Implementations/InputDeviceSwitcher.hpp>

InputDeviceSwitcher::InputDeviceSwitcher(Display* displayPtr)
{
	_deviceEnabledPropertyAtom = XInternAtom(displayPtr, DeviceEnabledPropertyName.toLocal8Bit().data(), true);
}

void InputDeviceSwitcher::SwitchDevice(Display* displayPtr, int deviceId, bool turnOn)
{
	unsigned char propertyValue = 0;
	if (turnOn)
	{
		propertyValue = 1;
	}

	// Setting property
	XIChangeProperty(displayPtr,
				deviceId,
				_deviceEnabledPropertyAtom,
				XA_INTEGER,
				8, // Is Enabled is 8-bit property
				PropModeReplace, // Replacing property
				&propertyValue,
				1); // Property is 1 byte
}
