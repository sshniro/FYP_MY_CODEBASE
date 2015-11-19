#ifndef PRINCIPLE_H
#define PRINCIPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_principle.h"

class Principle : public QMainWindow
{
	Q_OBJECT

public:
	Principle(QWidget *parent = 0);
	~Principle();

private:
	Ui::PrincipleClass ui;
};

#endif // PRINCIPLE_H
