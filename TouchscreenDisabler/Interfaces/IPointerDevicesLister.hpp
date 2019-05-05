#ifndef IPOINTERDEVICESLISTER_HPP
#define IPOINTERDEVICESLISTER_HPP

/**
  * @file Interface for getting pointing devices list
  */

#include <QObject>
#include <QString>
#include <QVector>
#include <X11/Xlib.h>

/**
  * Structure with information about one pointing device.
  */
typedef struct
{
	/**
	 * @brief Device ID.
	 */
	int Id;

	/**
	 * @brief Device name.
	 */
	QString Name;
} PointerDeviceInfo;

namespace Interfaces
{
	class IPointerDevicesLister : public QObject
	{
		Q_OBJECT

		public:

			/**
			 * @brief Lists attached physical pointer devices.
			 * @param displayPtr Pointer to display.
			 * @return List of physical pointer devices.
			 */
			virtual QVector<PointerDeviceInfo> ListPointerDevices(Display* displayPtr) = 0;

			/**
			 * @brief Searches for devices with given name. I hope that only one device with given name exist, but
			 * cant guarantee it.
			 * @param displayPtr Pointer to display.
			 * @param name Search for device with this name.
			 * @return Found devices
			 */
			virtual QVector<PointerDeviceInfo> FindPointerDevicesByName(Display* displayPtr, QString name) = 0;
	};
}

#endif // IPOINTERDEVICESLISTER_HPP
