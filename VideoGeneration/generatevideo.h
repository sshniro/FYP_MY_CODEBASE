#ifndef GENERATEVIDEO_H
#define GENERATEVIDEO_H

#include <QWidget>
#include "ui_generatevideo.h"

class GenerateVideo : public QWidget
{
	Q_OBJECT

public:
	GenerateVideo(QWidget *parent = 0);
	~GenerateVideo();

private:
	Ui::GenerateVideo ui;

public slots:
	//naming convention 
	//on_<sender>_<signal>()
	void on_generatePushButton_clicked();
};

#endif // GENERATEVIDEO_H
