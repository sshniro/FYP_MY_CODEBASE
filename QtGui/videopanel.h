#ifndef VIDEOPANEL_H
#define VIDEOPANEL_H

#include <QWidget>
#include "ui_videopanel.h"

class VideoPanel : public QWidget
{
	Q_OBJECT

public:
	VideoPanel(QWidget *parent = 0);
	~VideoPanel();

private:
	Ui::VideoPanel ui;
};

#endif // VIDEOPANEL_H
