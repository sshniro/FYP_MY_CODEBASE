#ifndef THREAD_CAMERANODE_H
#define THREAD_CAMERANODE_H

#include "QtCore\qthread.h"
#include "QtCore\qmutex.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

class NodeThread : public QThread
{
public:
	NodeThread();
	NodeThread(QMutex* mutex, Mat* outFrame);
	void run();
	~NodeThread();

	std::string videoLink;
	VideoCapture stream;
	bool isShown;
	bool isNotEnd;
private:
	QMutex* mutex;
	Mat* frame;
};

#endif