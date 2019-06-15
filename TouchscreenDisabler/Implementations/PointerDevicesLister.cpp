#include <Implementations/PointerDevicesLister.hpp>

QVector<Main::PointerDeviceInfo> PointerDevicesLister::ListPointerDevices(Display* displayPtr)
{
	int devicesNumber;
	auto devices = XListInputDevices(displayPtr, &devicesNumber);

	QVector<Main::PointerDeviceInfo> result;
	for (int i = 0; i < devicesNumber; i++)
	{
		auto deviceInfo = devices[i];

		// Filtering for pointer devices
		if (IsXExtensionPointer != deviceInfo.use)
		{
			continue;
		}

		Main::PointerDeviceInfo resultDevice;
		resultDevice.Id = deviceInfo.id;
		resultDevice.Name = QString::fromUtf8(deviceInfo.name);

		result.append(resultDevice);
	}

	return result;
}

QVector<Main::PointerDeviceInfo> PointerDevicesLister::FindPointerDevicesByName(Display* displayPtr, QString name)
{
	auto allDevices = ListPointerDevices(displayPtr);

	QVector<Main::PointerDeviceInfo> result;

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
