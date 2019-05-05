#ifndef POINTERDEVICESLISTER_HPP
#define POINTERDEVICESLISTER_HPP

#include <Interfaces/IPointerDevicesLister.hpp>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XI.h>

/**
  * @brief Class for getting physical pointer devices list.
  */
class PointerDevicesLister : public Interfaces::IPointerDevicesLister
{
	Q_OBJECT

	public:
		QVector<PointerDeviceInfo> ListPointerDevices(Display* displayPtr);
		QVector<PointerDeviceInfo> FindPointerDevicesByName(Display* displayPtr, QString name);
};


#endif // POINTERDEVICESLISTER_HPP
