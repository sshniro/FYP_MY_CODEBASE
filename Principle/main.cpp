#include "principle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Principle w;
	w.show();
	return a.exec();
}
