#ifndef DISPLAYGETTER_HPP
#define DISPLAYGETTER_HPP

#include <Interfaces/IDisplayGetter.hpp>

/**
 * @file Class to get pointer to Xorg display
 */
class DisplayGetter : public Interfaces::IDisplayGetter
{
	Q_OBJECT

	public:

		Display* GetDisplay();
		void FreeDisplay(Display* displayPtr);
};

#endif // DISPLAYGETTER_HPP
