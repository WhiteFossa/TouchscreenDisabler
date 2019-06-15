#ifndef POINTERDEVICESLISTER_HPP
#define POINTERDEVICESLISTER_HPP

#include <Interfaces/IPointerDevicesLister.hpp>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XI.h>

/**
  * @file Class for getting physical pointer devices list.
  */
class PointerDevicesLister : public Main::Interfaces::IPointerDevicesLister
{
	Q_OBJECT

	public:
		QVector<Main::PointerDeviceInfo> ListPointerDevices(Display* displayPtr);
		QVector<Main::PointerDeviceInfo> FindPointerDevicesByName(Display* displayPtr, QString name);
};


#endif // POINTERDEVICESLISTER_HPP
