#ifndef IDISPLAYGETTER_H
#define IDISPLAYGETTER_H

/**
  * @file Interface for getting Xorg display
  */

#include <QObject>
#include <X11/Xlib.h>

namespace Main
{
	namespace Interfaces
	{
		class IDisplayGetter : public QObject
		{
			Q_OBJECT

			public:

				/**
				 * @brief Call this method to get pointer to Xorg display.
				 * @return Pointer to Xorg display.
				 */
				virtual Display* GetDisplay() = 0;

				/**
				 * @brief Call to close display, returned by GetDisplay().
				 * @param displayPtr Pointer to display to close.
				 */
				virtual void FreeDisplay(Display* displayPtr) = 0;
		};
	}
}

#endif // IDISPLAYGETTER_H
