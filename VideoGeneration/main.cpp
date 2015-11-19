#include "generatevideo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GenerateVideo w;
	w.show();
	return a.exec();
}
