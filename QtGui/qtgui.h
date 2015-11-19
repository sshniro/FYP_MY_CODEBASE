#ifndef QTGUI_H
#define QTGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_qtgui.h"

class QtGui : public QMainWindow
{
	Q_OBJECT

public:
	QtGui(QWidget *parent = 0);
	~QtGui();

private:
	Ui::QtGuiClass ui;
};

#endif // QTGUI_H
