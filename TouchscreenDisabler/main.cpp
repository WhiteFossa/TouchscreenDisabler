#include <QApplication>
#include "touchscreendisabler.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TouchscreenDisabler w;
	w.show();

	return a.exec();
}
