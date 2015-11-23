#include "Thread_CameraNode.h"
#include "QtCore\qthread.h"
#include "QtCore\qdebug.h"

using namespace cv;
using namespace std;

NodeThread::NodeThread()
{
}

NodeThread::NodeThread(QMutex* m, Mat* outFrame)
{
	mutex = m;
	frame = outFrame;
	isShown = true;
	isNotEnd = true;
}

NodeThread::~NodeThread()
{
}

void NodeThread::run()
{
	qDebug() << this->currentThreadId << "running";

	QString s = QString::fromStdString(this->videoLink);
	QStringList sL = s.split('\\');

	while (stream.grab())
	{
		while (!isShown);
		isNotEnd = stream.read(*frame);
		isShown = false;
		//cvWaitKey(1);
	}
}