#include <Implementations/InputDeviceByNameSwitcher.hpp>

bool InputDeviceByNameSwitcher::SwitchDevice(QString deviceName, bool turnOn)
{
	// Getting display pointer
	auto displayGetter = new DisplayGetter();
	auto displayPtr = displayGetter->GetDisplay();

	// Searching for device
	auto pointerDevicesLister = new PointerDevicesLister();
	auto foundDevices = pointerDevicesLister->FindPointerDevicesByName(displayPtr, deviceName);

	// Freeing stuff
	SafeDelete(pointerDevicesLister);
	displayGetter->FreeDisplay(displayPtr);
	SafeDelete(displayGetter);

	if (0 == foundDevices.count())
	{
		// No devices with this name
		return false;
	}

	// We have at least one device with this name. I suppose that it will be always one, but anyway
	// iterating through them.
	auto inputDeviceSwitcher = new InputDeviceSwitcher();

	for (auto device : foundDevices)
	{
		inputDeviceSwitcher->SwitchDevice(device.Id, turnOn);
	}

	SafeDelete(inputDeviceSwitcher);

	return true;
}
