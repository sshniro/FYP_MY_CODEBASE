#include "generatevideo.h"
#include <QtWidgets/QApplication>

int mainXD(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GenerateVideo w;
	w.show();
	return a.exec();
}
