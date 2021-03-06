#include "ui_touchscreendisabler.h"
#include "touchscreendisabler.h"
#include <ControlledInputDevicesDialog/Implementations/ControlledInputDevicesDialog.hpp>
#include <QDesktopWidget>

TouchscreenDisabler::TouchscreenDisabler(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::TouchscreenDisabler)
{
	ui->setupUi(this);

	// Centering main window
	this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));

	// Signals-slots connection
	QObject::connect(ui->btnListDevices, SIGNAL(clicked(bool)), this, SLOT(ListDevices()));
	QObject::connect(ui->btnDisable, SIGNAL(clicked(bool)), this, SLOT(DisableDevice()));
	QObject::connect(ui->btnEnable, SIGNAL(clicked(bool)), this, SLOT(EnableDevice()));
	QObject::connect(ui->btnSetupControlledDevices, SIGNAL(clicked(bool)), this, SLOT(SlotShowControlledInputDevicesDialog()));

	// Getting display
	_displayGetter = new DisplayGetter();
	_displayPtr = _displayGetter->GetDisplay();

	// Ponter devices lister
	_pointerDevicesLister = new PointerDevicesLister();

	// Controlled input devices container
	_controlledInputDevicesContainer = new ControlledInputDevicesContainer();

	// TODO: Add devices list load here
	_controlledInputDevicesContainer->Add("Logitech M510");
}

void TouchscreenDisabler::ListDevices()
{
	auto pointerDevices = _pointerDevicesLister->ListPointerDevices(_displayPtr);

	for (auto device : pointerDevices)
	{
		qDebug() << QString("Device Id=%1, Name=%2").arg(device.Id).arg(device.Name);
	}
}

void TouchscreenDisabler::DisableDevice()
{
	_controlledInputDevicesContainer->SetState(false);
}

void TouchscreenDisabler::EnableDevice()
{
	_controlledInputDevicesContainer->SetState(true);
}

void TouchscreenDisabler::SlotShowControlledInputDevicesDialog()
{
	auto dialog = new ControlledInputDevicesDialog::ControlledInputDevicesDialog(_controlledInputDevicesContainer, this);

	auto result = dialog->exec();

	qDebug() << result;

	SafeDelete(dialog);
}

TouchscreenDisabler::~TouchscreenDisabler()
{
	SafeDelete(_controlledInputDevicesContainer);
	SafeDelete(_pointerDevicesLister);

	_displayGetter->FreeDisplay(_displayPtr);
	SafeDelete(_displayGetter);

	delete ui;
}
