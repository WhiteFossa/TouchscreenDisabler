#include <ControlledInputDevicesDialog/Implementations/ControlledInputDevicesDialog.hpp>
#include <QtGlobal>
#include <QString>
#include <Auxiliary.hpp>

namespace ControlledInputDevicesDialog
{
	ControlledInputDevicesDialog::ControlledInputDevicesDialog()
	{
		qFatal(QString("Parameterless constructor is not allowed")
				.toLocal8Bit()
				.data());
	}

	ControlledInputDevicesDialog::ControlledInputDevicesDialog(Main::Interfaces::IControlledInputDevicesContainer* controlledDevicesContainer,
									QWidget* parent, Qt::WindowFlags flags)
									: IControlledInputDevicesDialog(parent, flags),
									ui(new Ui::dControlledInputDevices)
	{
		ui->setupUi(this);

		_devicesContainer = controlledDevicesContainer;
	}

	ControlledInputDevicesDialog::~ControlledInputDevicesDialog()
	{
		SafeDelete(ui);
	}
}

