#ifndef IDEVICESWITCHER_HPP
#define IDEVICESWITCHER_HPP

/**
  * @file Interface for turning input device on and off.
  */

#include <QObject>
#include <QString>
#include <X11/Xlib.h>

namespace Main
{
	namespace Interfaces
	{
		class IInputDeviceSwitcher : public QObject
		{
			Q_OBJECT

			public:

				/**
				 * @brief Turns given input device on and off.
				 * @param deviceId Which device to turn.
				 * @param turnOn If true, then device will be turn on, if false - off.
				 */
				virtual void SwitchDevice(int deviceId, bool turnOn) = 0;
		};
	}
}

#endif // IDEVICESWITCHER_HPP
