#ifndef THREADFORNODE_H
#define THREADFORNODE_H

#include <QObject>
#include "QtCore\qthread.h"
#include "qdebug.h"
#include "Models.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace models;
using namespace cv;

class MessagePasser;

class ThreadForNode : public QThread
{
	Q_OBJECT

public:
	ThreadForNode();
	~ThreadForNode();
	void run();
	void updateProfileList(ProfileTransferObj profile);

	string nodeId;
	string videoLink; // temp

signals:
	void sendProfileToNode(ProfileTransferObj profile, ThreadForNode* nodeThread);

private:
	MessagePasser* msgPasser;
	Mat frame;
};

#endif // THREADFORNODE_H
