#ifndef IINPUTDEVICEBYNAMESWITCHER_HPP
#define IINPUTDEVICEBYNAMESWITCHER_HPP

/**
  * @file Interface to switch input devices on and off by device name.
  */

#include <QObject>
#include <QString>

namespace Main
{
	namespace Interfaces
	{
		class IInputDeviceByNameSwitcher : public QObject
		{
			Q_OBJECT

			public:

				/**
				 * @brief Trying to switch input device with given name on or off.
				 * @param deviceName Device name (as returned by xinput).
				 * @param turnOn True to turn device on, false to turn device off.
				 * @return True if given device was found and commanded on/off, false otherwise.
				 */
				virtual bool SwitchDevice(QString deviceName, bool turnOn) = 0;
		};
	}
}

#endif // IINPUTDEVICEBYNAMESWITCHER_HPP
