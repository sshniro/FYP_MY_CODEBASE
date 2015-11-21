
#include <QtWidgets/QApplication>
#include <QtGui/qimage.h>
#include <QtWidgets\qlabel.h>


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

using namespace cv;
using namespace std;

QImage Mat2QImage(cv::Mat const& src);

int mainX(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QtTest2 w;
	//w.show();
	//return a.exec();
	VideoCapture cap1("C:\\Projects\\PRG1.avi");
	VideoCapture cap2("C:\\Projects\\PRG6.avi");
	Mat cameraFrame;
	Mat greyFrame;
	cap2.read(cameraFrame);
	QImage myImage;
	myImage = Mat2QImage(cameraFrame);

	QLabel myLabel;
	myLabel.setPixmap(QPixmap::fromImage(myImage));

	myLabel.show();
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");
	stmt->execute("DROP TABLE IF EXISTS test");
	stmt->execute("CREATE TABLE test(id INT, label VARCHAR(50))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'KasunTest')");

	delete stmt;
	delete con;
	cvWaitKey(0);

	return a.exec();

}

QImage Mat2QImage(cv::Mat const& src)
{
	QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

	const float scale = 255.0;

	if (src.depth() == CV_8U) {
		if (src.channels() == 1) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					int level = src.at<quint8>(i, j);
					dest.setPixel(j, i, qRgb(level, level, level));
				}
			}
		}
		else if (src.channels() == 3) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
					dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
				}
			}
		}
	}
	else if (src.depth() == CV_32F) {
		if (src.channels() == 1) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					int level = scale * src.at<float>(i, j);
					dest.setPixel(j, i, qRgb(level, level, level));
				}
			}
		}
		else if (src.channels() == 3) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
					dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
				}
			}
		}
	}

	return dest;
}

//Code Dump
/*

for (int i = 0; i < cmaskImage.rows; i++)
{
QString line = "";
for (int j = 0; j < cmaskImage.cols; j++)
{
int value = cmaskImage.at<uchar>(i, j);
line += QString::number(value) + " ";
}
qDebug() << line;
}

*/