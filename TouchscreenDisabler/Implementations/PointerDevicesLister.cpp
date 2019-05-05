#include <Implementations/PointerDevicesLister.hpp>

QVector<PointerDeviceInfo> PointerDevicesLister::ListPointerDevices(Display* displayPtr)
{
	int devicesNumber;
	XDeviceInfo* devices = XListInputDevices(displayPtr, &devicesNumber);

	QVector<PointerDeviceInfo> result;
	for (int i = 0; i < devicesNumber; i++)
	{
		auto deviceInfo = devices[i];

		// Filtering for pointer devices
		if (IsXExtensionPointer != deviceInfo.use)
		{
			continue;
		}

		PointerDeviceInfo resultDevice;
		resultDevice.Id = deviceInfo.id;
		resultDevice.Name = QString::fromUtf8(deviceInfo.name);

		result.append(resultDevice);
	}

	return result;
}

QVector<PointerDeviceInfo> PointerDevicesLister::FindPointerDevicesByName(Display* displayPtr, QString name)
{
	auto allDevices = ListPointerDevices(displayPtr);

	QVector<PointerDeviceInfo> result;

	for (auto device : allDevices)
	{
		if (name != device.Name)
		{
			continue;
		}

		result.append(device);
	}

	return result;
}
