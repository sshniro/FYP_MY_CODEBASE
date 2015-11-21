#ifndef VIDEOGENERATION_H
#define VIDEOGENERATION_H

#include <QtWidgets/QMainWindow>
#include "ui_videogeneration.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;
using namespace sql;
using namespace mysql;
using namespace cv;


class VideoGeneration : public QMainWindow
{
	Q_OBJECT

public:
	VideoGeneration(QWidget *parent = 0);
	~VideoGeneration();

public slots:
	void on_generateVideoPushButton_clicked();

private:
	Ui::VideoGenerationClass ui;
};

#endif // VIDEOGENERATION_H
