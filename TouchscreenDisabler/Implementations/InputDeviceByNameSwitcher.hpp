#ifndef INPUTDEVICEBYNAMESWITCHER_HPP
#define INPUTDEVICEBYNAMESWITCHER_HPP

#include <Interfaces/IInputDeviceByNameSwitcher.hpp>

/**
 * @file Class to turn input devices on and off by their names.
 */
#include <Auxiliary.hpp>
#include <Interfaces/IDisplayGetter.hpp>
#include <Interfaces/IPointerDevicesLister.hpp>
#include <Interfaces/IInputDeviceSwitcher.hpp>
#include <Implementations/DisplayGetter.hpp>
#include <Implementations/PointerDevicesLister.hpp>
#include <Implementations/InputDeviceSwitcher.hpp>

class InputDeviceByNameSwitcher : public Interfaces::IInputDeviceByNameSwitcher
{
	Q_OBJECT

	public:
		bool SwitchDevice(QString deviceName, bool turnOn);

};

#endif // INPUTDEVICEBYNAMESWITCHER_HPP
