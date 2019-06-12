#include <Implementations/ControlledInputDevicesContainer.hpp>
#include <Implementations/InputDeviceByNameSwitcher.hpp>
#include <Auxiliary.hpp>
#include <QtGlobal>

ControlledInputDevicesContainer::ControlledInputDevicesContainer()
{
	SetState(true); // By default all devices are enabled
	_switcher = new InputDeviceByNameSwitcher();
}

void ControlledInputDevicesContainer::Add(QString deviceName)
{
	if (_devices.contains(deviceName))
	{
		return;
	}

	_devices.append(deviceName);
	_switcher->SwitchDevice(deviceName, _state);
}

void ControlledInputDevicesContainer::Remove(QString deviceName)
{
	if (!_devices.contains(deviceName))
	{
		qFatal(QString("Attempt to remove device \"%1\", that isn't in controlled devices list")
			   .arg(deviceName)
			   .toLocal8Bit()
			   .data());
	}

	_devices.removeOne(deviceName);

	// Enabling device, we don't control it anymore
	_switcher->SwitchDevice(deviceName, true);
}

QVector<QString> ControlledInputDevicesContainer::List()
{
	return _devices;
}

void ControlledInputDevicesContainer::SetState(bool turnOn)
{
	_state = turnOn;

	for (auto device : _devices)
	{
		_switcher->SwitchDevice(device, _state);
	}
}

bool ControlledInputDevicesContainer::GetState()
{
	return _state;
}

void ControlledInputDevicesContainer::SetStateSlot(bool turnOn)
{
	SetState(turnOn);
}

ControlledInputDevicesContainer::~ControlledInputDevicesContainer()
{
	SafeDelete(_switcher);
}


