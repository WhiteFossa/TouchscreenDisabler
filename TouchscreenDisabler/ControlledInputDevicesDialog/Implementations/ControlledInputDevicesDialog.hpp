#ifndef CONTROLLEDINPUTDEVICESDIALOG_HPP
#define CONTROLLEDINPUTDEVICESDIALOG_HPP

/**
  * @file Class with dialog, allowing to select which input devices will be controlled.
  */

#include <qcoreevent.h>
#include <QStyleOption>
#include <QDataStream>
#include <QTextStream>
#include <ControlledInputDevicesDialog/Interfaces/IControlledInputDevicesDialog.hpp>
#include <Interfaces/IControlledInputDevicesContainer.hpp>
#include <Implementations/DisplayGetter.hpp>
#include <Implementations/PointerDevicesLister.hpp>
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

			/**
			 * @brief Resets dialod, loads controlled devices from container and available devices from Xorg.
			 */
			void Reset();

			/**
			 * @brief Populates available devices list using data from Xorg and contents of controlled devices list.
			 */
			void PopulateAvailableDevicesList();

			/**
			 * @brief Applies changes, i.e. putting new devices list into container.
			 */
			void Apply();

		private slots:

			/**
			 * @brief Called when need to reset settings
			 */
			void SlotReset();

			/**
			 * @brief Call when selection in available devices list changed.
			 */
			void SlotAvailableDevicesSelectionChanged();

			/**
			 * @brief Call when selection in controlled devices list changed.
			 */
			void SlotControlledDevicesSelectionChanged();

			/**
			 * @brief Call when "To Controlled List" button is pressed.
			 */
			void SlotButtonToControlledClicked();

			/**
			 * @brief Call when "To Available List" button is pressed.
			 */
			void SlotButtonToAvailableClicked();

			/**
			 * @brief Call when need to apply settings exist.
			 */
			void SlotApply();
	};
}

#endif // CONTROLLEDINPUTDEVICESDIALOG_HPP
