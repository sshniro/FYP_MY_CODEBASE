#include "videogeneration.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VideoGeneration w;
	w.show();
	
	return a.exec();
}
