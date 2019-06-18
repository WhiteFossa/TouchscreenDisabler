#include <ControlledInputDevicesDialog/Implementations/ControlledInputDevicesDialog.hpp>
#include <QtGlobal>
#include <QString>
#include <Auxiliary.hpp>
#include <QPushButton>
#include <QDebug>

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
									: IControlledInputDevicesDialog(controlledDevicesContainer, parent, flags),
									ui(new Ui::dControlledInputDevices)
	{
		ui->setupUi(this);

		// Signal-slot connection

		// Reset button
		QObject::connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked(bool)), this, SLOT(SlotReset()));

		// Apply button
		QObject::connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)), this, SLOT(SlotApply()));

		// Selection change in lists
		QObject::connect(ui->listAvailable, SIGNAL(itemSelectionChanged()), this, SLOT(SlotAvailableDevicesSelectionChanged()));
		QObject::connect(ui->listControlled, SIGNAL(itemSelectionChanged()), this, SLOT(SlotControlledDevicesSelectionChanged()));

		// Move device to controlled list
		QObject::connect(ui->btnToControlled, SIGNAL(clicked(bool)), this, SLOT(SlotButtonToControlledClicked()));

		// Move device to available list
		QObject::connect(ui->btnToAvailable, SIGNAL(clicked(bool)), this, SLOT(SlotButtonToAvailableClicked()));

		// Applying settings on dialog accept
		QObject::connect(this, SIGNAL(accepted()), this, SLOT(SlotApply()));

		// Resetting settings on dialog cancel
		QObject::connect(this, SIGNAL(rejected()), this, SLOT(SlotReset()));

		_devicesContainer = controlledDevicesContainer;

		// By default nothing is selected, so movement buttons are disabled
		ui->btnToControlled->setEnabled(false);
		ui->btnToAvailable->setEnabled(false);

		// Loading initial settings
		Reset();
	}

	ControlledInputDevicesDialog::~ControlledInputDevicesDialog()
	{
		SafeDelete(ui);
	}

	void ControlledInputDevicesDialog::Reset()
	{
		// Loading controlled devices from container
		ui->listControlled->clear();

		for (auto device : _devicesContainer->List())
		{
			ui->listControlled->addItem(device);
		}

		PopulateAvailableDevicesList();
	}

	void ControlledInputDevicesDialog::PopulateAvailableDevicesList()
	{
		auto displayGetter = new DisplayGetter();
		auto pointerDevicesLister = new PointerDevicesLister();

		auto xorgDevicesList = pointerDevicesLister->ListPointerDevices(displayGetter->GetDisplay());

		SafeDelete(pointerDevicesLister);
		SafeDelete(displayGetter);

		// Populating available devices list
		ui->listAvailable->clear();
		for (auto device : xorgDevicesList)
		{
			if (0 == ui->listControlled->findItems(device.Name, Qt::MatchExactly).count())
			{
				// No such items in controlled list, adding
				ui->listAvailable->addItem(device.Name);
			}
		}

		// Disabling "To Controlled" button, because selection is lost
		ui->btnToControlled->setEnabled(false);
	}

	void ControlledInputDevicesDialog::SlotReset()
	{
		Reset();
	}

	void ControlledInputDevicesDialog::SlotAvailableDevicesSelectionChanged()
	{
		ui->btnToControlled->setEnabled(nullptr != ui->listAvailable->currentItem());
	}

	void ControlledInputDevicesDialog::SlotControlledDevicesSelectionChanged()
	{
		ui->btnToAvailable->setEnabled(nullptr != ui->listControlled->currentItem());
	}

	void ControlledInputDevicesDialog::SlotButtonToControlledClicked()
	{
		auto selectedItem = ui->listAvailable->currentItem();

		if (nullptr == selectedItem)
		{
			qFatal(QString("Item in Available list isn't selected!")
				   .toLocal8Bit()
				   .data());
		}

		ui->listControlled->addItem(selectedItem->text());

		// Don't need to remove from available list, because it will be regenerated
		PopulateAvailableDevicesList();
	}

	void ControlledInputDevicesDialog::SlotButtonToAvailableClicked()
	{
		auto selectedItem = ui->listControlled->currentItem();

		if (nullptr == selectedItem)
		{
			qFatal(QString("Item in Controlled list isn't selected!")
				   .toLocal8Bit()
				   .data());
		}

		// Removing item
		ui->listControlled->takeItem(ui->listControlled->row(selectedItem));

		// Resetting selection
		ui->listControlled->clearSelection();
		ui->btnToAvailable->setEnabled(false);

		PopulateAvailableDevicesList();
	}

	void ControlledInputDevicesDialog::Apply()
	{
		qDebug() << "Apply settings";
	}

	void ControlledInputDevicesDialog::SlotApply()
	{
		// Iterating through container and removing everything that not in controlled list
		auto currentControlledDevices = _devicesContainer->List();

		for(auto device : currentControlledDevices)
		{
			if (0 == ui->listControlled->findItems(device, Qt::MatchExactly).count())
			{
				// Need to remove it
				_devicesContainer->Remove(device);
			}
		}

		// Iterating through controlled devices list and adding everything which isn't in container
		currentControlledDevices = _devicesContainer->List();

		for (auto device : ui->listControlled->findItems("*", Qt::MatchWildcard))
		{
			if (!currentControlledDevices.contains(device->text()))
			{
				_devicesContainer->Add(device->text());
			}
		}
	}
}

