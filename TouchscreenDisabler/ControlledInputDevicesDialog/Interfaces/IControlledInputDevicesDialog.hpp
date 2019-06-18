#ifndef ICONTROLLEDINPUTDEVICESDIALOG_HPP
#define ICONTROLLEDINPUTDEVICESDIALOG_HPP

/**
  * @file Interface for controlled input devices dialog.
  */

#include <QDialog>
#include <QWidget>
#include <Interfaces/IControlledInputDevicesContainer.hpp>

namespace ControlledInputDevicesDialog
{
	namespace Interfaces
	{
		class IControlledInputDevicesDialog : public QDialog
		{
			Q_OBJECT

			public:

			protected:

				IControlledInputDevicesDialog() : QDialog() {}

				IControlledInputDevicesDialog(Main::Interfaces::IControlledInputDevicesContainer* controlledDevicesContainer,
											  QWidget* parent, Qt::WindowFlags flags) : QDialog(parent, flags)
				{
					Q_UNUSED(controlledDevicesContainer)
				}
		};
	}
}

#endif // ICONTROLLEDINPUTDEVICESDIALOG_HPP
