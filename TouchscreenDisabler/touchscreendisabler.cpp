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

	// Input device switcher
	_inputDeviceSwitcher = new InputDeviceSwitcher(_displayPtr);

}

void TouchscreenDisabler::ListDevices()
{
	//QVector<PointerDeviceInfo> pointerDevices = _pointerDevicesLister->FindPointerDevicesByName(_displayPtr, "Logitech M510");
	auto pointerDevices = _pointerDevicesLister->ListPointerDevices(_displayPtr);

	for (auto device : pointerDevices)
	{
		qDebug() << QString(QObject::trUtf8("Device Id=%1, Name=%2")).arg(device.Id).arg(device.Name);
	}
}

void TouchscreenDisabler::DisableDevice()
{
	auto displayGetter = new DisplayGetter();
	auto displayPtr = displayGetter->GetDisplay();

	QVector<PointerDeviceInfo> pointerDevices = _pointerDevicesLister->FindPointerDevicesByName(displayPtr, "Logitech M510");
	for (auto device : pointerDevices)
	{
		_inputDeviceSwitcher->SwitchDevice(displayPtr, device.Id, false);
	}

	displayGetter->FreeDisplay(displayPtr);
	SafeDelete(displayGetter);
}

void TouchscreenDisabler::EnableDevice()
{
	auto displayGetter = new DisplayGetter();
	auto displayPtr = displayGetter->GetDisplay();

	QVector<PointerDeviceInfo> pointerDevices = _pointerDevicesLister->FindPointerDevicesByName(displayPtr, "Logitech M510");
	for (auto device : pointerDevices)
	{
		_inputDeviceSwitcher->SwitchDevice(displayPtr, device.Id, true);
	}

	displayGetter->FreeDisplay(displayPtr);
	SafeDelete(displayGetter);
}

TouchscreenDisabler::~TouchscreenDisabler()
{
	SafeDelete(_inputDeviceSwitcher);
	SafeDelete(_pointerDevicesLister);

	_displayGetter->FreeDisplay(_displayPtr);
	SafeDelete(_displayGetter);

	delete ui;
}
