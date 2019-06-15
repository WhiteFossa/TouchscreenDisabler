#ifndef INPUTDEVICESWITCHER_HPP
#define INPUTDEVICESWITCHER_HPP

#include <Auxiliary.hpp>
#include <Interfaces/IInputDeviceSwitcher.hpp>
#include <Interfaces/IDisplayGetter.hpp>
#include <Implementations/DisplayGetter.hpp>
#include <X11/Xatom.h>
#include <X11/extensions/XInput2.h>

/**
 * @files Class to turn devices on and off by their IDs
 */
class InputDeviceSwitcher : public Main::Interfaces::IInputDeviceSwitcher
{
	Q_OBJECT

	public:
		void SwitchDevice(int deviceId, bool turnOn);

	private:

		/**
		 * @brief Property, containing Device Enable flag.
		 */
		const QString DeviceEnabledPropertyName = "Device Enabled";
};

#endif // INPUTDEVICESWITCHER_HPP
