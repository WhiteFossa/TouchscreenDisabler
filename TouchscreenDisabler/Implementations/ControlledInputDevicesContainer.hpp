#ifndef CONTROLLEDINPUTDEVICESCONTAINER_HPP
#define CONTROLLEDINPUTDEVICESCONTAINER_HPP

/**
  * @file Class to control multiple input devices at time.
  */

#include <Interfaces/IControlledInputDevicesContainer.hpp>
#include <Interfaces/IInputDeviceByNameSwitcher.hpp>

class ControlledInputDevicesContainer : public Interfaces::IControlledInputDevicesContainer
{
	Q_OBJECT

	public:

		ControlledInputDevicesContainer();
		~ControlledInputDevicesContainer();

		void Add(QString deviceName);
		void Remove(QString deviceName);
		QVector<QString> List();
		void SetState(bool turnOn);
		bool GetState();

	public slots:
		void SetStateSlot(bool turnOn);

	private:

		/**
		 * @brief Controlled devices names.
		 */
		QVector<QString> _devices;

		/**
		 * @brief Container state. True if devices enabled.
		 */
		bool _state;

		/**
		 * @brief Pointer to devices switcher.
		 */
		Interfaces::IInputDeviceByNameSwitcher* _switcher;
};

#endif // CONTROLLEDINPUTDEVICESCONTAINER_HPP
