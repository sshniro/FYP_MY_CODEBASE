#include "videogeneration.h"
#include <QtWidgets/QApplication>

int mainXD(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VideoGeneration w;
	w.show();
	
	return a.exec();
}
