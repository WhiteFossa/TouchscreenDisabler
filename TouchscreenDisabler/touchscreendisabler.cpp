#include "ui_touchscreendisabler.h"
#include "touchscreendisabler.h"

TouchscreenDisabler::TouchscreenDisabler(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::TouchscreenDisabler)
{
	ui->setupUi(this);

	// Signals-slots connection
	QObject::connect(ui->btnListDevices, SIGNAL(clicked(bool)), this, SLOT(ListDevices()));
	QObject::connect(ui->btnDisable, SIGNAL(clicked(bool)), this, SLOT(DisableDevice()));
	QObject::connect(ui->btnEnable, SIGNAL(clicked(bool)), this, SLOT(EnableDevice()));

	// Getting display
	_displayGetter = new DisplayGetter();
	_displayPtr = _displayGetter->GetDisplay();

	// Ponter devices lister
	_pointerDevicesLister = new PointerDevicesLister();

	// Device switcher
	_inputDeviceByNameSwitcher = new InputDeviceByNameSwitcher();
}

void TouchscreenDisabler::ListDevices()
{
	//QVector<PointerDeviceInfo> pointerDevices = _pointerDevicesLister->FindPointerDevicesByName(_displayPtr, "Logitech M510");
	auto pointerDevices = _pointerDevicesLister->ListPointerDevices(_displayPtr);

	for (auto device : pointerDevices)
	{
		qDebug() << QString("Device Id=%1, Name=%2").arg(device.Id).arg(device.Name);
	}
}

void TouchscreenDisabler::DisableDevice()
{
	_inputDeviceByNameSwitcher->SwitchDevice("Logitech M510", false);
}

void TouchscreenDisabler::EnableDevice()
{
	_inputDeviceByNameSwitcher->SwitchDevice("Logitech M510", true);
}

TouchscreenDisabler::~TouchscreenDisabler()
{
	SafeDelete(_inputDeviceByNameSwitcher);
	SafeDelete(_pointerDevicesLister);

	_displayGetter->FreeDisplay(_displayPtr);
	SafeDelete(_displayGetter);

	delete ui;
}
