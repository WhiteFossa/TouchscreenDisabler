#ifndef TOUCHSCREENDISABLER_H
#define TOUCHSCREENDISABLER_H

#include <QMainWindow>
#include <QDebug>
#include <Auxiliary.hpp>
#include <Interfaces/IDisplayGetter.hpp>
#include <Interfaces/IPointerDevicesLister.hpp>
#include <Interfaces/IInputDeviceByNameSwitcher.hpp>
#include <Interfaces/IControlledInputDevicesContainer.hpp>
#include <Implementations/DisplayGetter.hpp>
#include <Implementations/PointerDevicesLister.hpp>
#include <Implementations/InputDeviceByNameSwitcher.hpp>
#include <Implementations/ControlledInputDevicesContainer.hpp>
#include <X11/Xlib.h>

namespace Ui {
	class TouchscreenDisabler;
}

class TouchscreenDisabler : public QMainWindow
{
		Q_OBJECT

	public:
		explicit TouchscreenDisabler(QWidget *parent = 0);
		~TouchscreenDisabler();

	public slots:
		/**
		 * @brief List attached pointer devices
		 */
		void ListDevices();

		/**
		 * @brief Disable hardcoded device
		 */
		void DisableDevice();

		/**
		 * @brief Enable hardcoded device
		 */
		void EnableDevice();

	private:
		Ui::TouchscreenDisabler *ui;

		/**
		 * @brief Class to get pointer to X display.
		 */
		Interfaces::IDisplayGetter* _displayGetter = nullptr;

		/**
		 * @brief Default display (i.e. one, specified by Display environment variable).
		 */
		Display* _displayPtr = nullptr;

		/**
		 * @brief Class to get pointer devices list.
		 */
		Interfaces::IPointerDevicesLister* _pointerDevicesLister = nullptr;


		/**
		 * @brief Pointer to container with controlled input devices.
		 */
		Interfaces::IControlledInputDevicesContainer* _controlledInputDevicesContainer = nullptr;
};

#endif // TOUCHSCREENDISABLER_H
