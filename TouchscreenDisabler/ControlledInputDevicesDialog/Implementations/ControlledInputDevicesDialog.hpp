#ifndef CONTROLLEDINPUTDEVICESDIALOG_HPP
#define CONTROLLEDINPUTDEVICESDIALOG_HPP

/**
  * @file Class with dialog, allowing to select which input devices will be controlled.
  */

#include <ControlledInputDevicesDialog/Interfaces/IControlledInputDevicesDialog.hpp>
#include <Interfaces/IControlledInputDevicesContainer.hpp>
#include <ui_ControlledInputDevicesDialog.h>

namespace ControlledInputDevicesDialog
{
	class ControlledInputDevicesDialog : public Interfaces::IControlledInputDevicesDialog
	{
		Q_OBJECT

		public:

			/**
			 * @brief Default constructor is not allowed, will call qFatal().
			 */
			ControlledInputDevicesDialog();

			/**
			 * @brief Constructor.
			 * @param controlledDevicesContainer Pointer to controlled devices container. List of controlled devices will be got from it,
			 * container contents will be updated on "OK"/"Apply".
			 * @param parent Parent widget.
			 * @param flags Window flags.
			 */
			ControlledInputDevicesDialog(Main::Interfaces::IControlledInputDevicesContainer* controlledDevicesContainer,
										 QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

			~ControlledInputDevicesDialog();

		private:

			Ui::dControlledInputDevices* ui;

			/**
			 * @brief Devices are read from here / wrote here.
			 */
			Main::Interfaces::IControlledInputDevicesContainer* _devicesContainer;
	};
}

#endif // CONTROLLEDINPUTDEVICESDIALOG_HPP
