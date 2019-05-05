#ifndef INPUTDEVICESWITCHER_HPP
#define INPUTDEVICESWITCHER_HPP

#include <Interfaces/IInputDeviceSwitcher.hpp>
#include <X11/Xatom.h>
#include <X11/extensions/XInput2.h>

class InputDeviceSwitcher : public Interfaces::IInputDeviceSwitcher
{
	Q_OBJECT

	public:
		InputDeviceSwitcher(Display* displayPtr);

		void SwitchDevice(Display* displayPtr, int deviceId, bool turnOn);

	private:

		/**
		 * @brief Property, containing Device Enable flag.
		 */
		const QString DeviceEnabledPropertyName = "Device Enabled";

		/**
		 * @brief Atom, selected by DeviceEnabledPropertyName
		 */
		Atom _deviceEnabledPropertyAtom;
};

#endif // INPUTDEVICESWITCHER_HPP
