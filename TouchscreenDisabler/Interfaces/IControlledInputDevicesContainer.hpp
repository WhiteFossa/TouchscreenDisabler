#ifndef ICONTROLLEDINPUTDEVICESCONTAINER_HPP
#define ICONTROLLEDINPUTDEVICESCONTAINER_HPP

/**
  * @file Interface with controlled devices container. Container have a state (enabled or disabled) and newly added devices
  * getting this state.
  */

#include <QObject>
#include <QString>
#include <QVector>

namespace Interfaces
{
	class IControlledInputDevicesContainer : public QObject
	{
		Q_OBJECT

		public:

			/**
			 * @brief Adds device to containter. Device getting current container state.
			 * @param deviceName Device name (as in xinput output).
			 */
			virtual void Add(QString deviceName) = 0;

			/**
			 * @brief Removes device from container. Turns device on before removal.
			 * @param deviceName Device name (as in xinput output).
			 */
			virtual void Remove(QString deviceName) = 0;

			/**
			 * @brief Returns controlled devices list.
			 * @return Controlled devices list.
			 */
			virtual QVector<QString> List() = 0;

			/**
			 * @brief Turns all controlled devices on or off.
			 * @param turnOn If true, then turn controlled devices on.
			 */
			virtual void SetState(bool turnOn) = 0;

			/**
			 * @brief Gets container state.
			 * @return If true, then devices is turned on.
			 */
			virtual bool GetState() = 0;

		public slots:

			/**
			 * @brief Identical to SetState(), but slot.
			 * @param turnOn If true, then turn controlled devices on.
			 */
			virtual void SetStateSlot(bool turnOn) = 0;
	};
}

#endif // ICONTROLLEDINPUTDEVICESCONTAINER_HPP
