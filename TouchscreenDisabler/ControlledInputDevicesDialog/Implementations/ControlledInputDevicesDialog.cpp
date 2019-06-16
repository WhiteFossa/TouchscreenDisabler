#include <ControlledInputDevicesDialog/Implementations/ControlledInputDevicesDialog.hpp>
#include <QtGlobal>
#include <QString>
#include <Auxiliary.hpp>
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
									: IControlledInputDevicesDialog(parent, flags),
									ui(new Ui::dControlledInputDevices)
	{
		ui->setupUi(this);

		// Signal-slot connection
		QObject::connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(SlotButtonBoxClicked(QAbstractButton*)));
		QObject::connect(ui->listAvailable, SIGNAL(itemSelectionChanged()), this, SLOT(SlotAvailableDevicesSelectionChanged()));
		QObject::connect(ui->listControlled, SIGNAL(itemSelectionChanged()), this, SLOT(SlotControlledDevicesSelectionChanged()));
		QObject::connect(ui->btnToControlled, SIGNAL(clicked(bool)), this, SLOT(SlotButtonToControlledClicked()));
		QObject::connect(ui->btnToAvailable, SIGNAL(clicked(bool)), this, SLOT(SlotButtonToAvailableClicked()));

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

	void ControlledInputDevicesDialog::SlotButtonBoxClicked(QAbstractButton* button)
	{
		if (button == (QAbstractButton*)ui->buttonBox->button(QDialogButtonBox::Reset))
		{
			// Reset button
			Reset();
		}
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
}

