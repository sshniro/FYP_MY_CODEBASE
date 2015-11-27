#include "qttesting.h"

QtTesting::QtTesting(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	ThreadForNode* thread1 = new ThreadForNode();
	ThreadForNode* thread2 = new ThreadForNode();

	connect(thread1, SIGNAL(sendFrameToMain(QImage, ThreadForNode*)), this, SLOT(recieveFrameFromThreads(QImage, ThreadForNode*)));
	connect(thread2, SIGNAL(sendFrameToMain(QImage, ThreadForNode*)), this, SLOT(recieveFrameFromThreads(QImage, ThreadForNode*)));

	this->threadCount = 2;

	thread1->nodeId = "C001";
	thread2->nodeId = "C002";

	this->lblMap["C001"] = ui.lblCamera1;
	this->lblMap["C002"] = ui.lblCamera2;

	thread1->videoLink = "E:/Final Year/project/human tracking/coding/Videos/PRG6.avi";
	thread2->videoLink = "E:/Final Year/project/human tracking/coding/Videos/PRG9.avi";

	thread1->start();
	thread2->start();
}

QtTesting::~QtTesting()
{

}


void QtTesting::recieveFrameFromThreads(QImage outImage, ThreadForNode* thread)
{
	int x = outImage.byteCount();
	if (nodeMap.count(thread->nodeId) == 0)
	{
		frameMap[thread->nodeId] = outImage;
		nodeMap[thread->nodeId] = thread;
	}
	if (nodeMap.size() == threadCount)
	{
		for (map<string, QImage>::const_iterator i = frameMap.begin(); i != frameMap.end(); i++)
		{
			lblMap[i->first]->setPixmap(QPixmap::fromImage(frameMap[i->first]));
		}
		for (map<string, ThreadForNode*>::const_iterator i = nodeMap.begin(); i != nodeMap.end(); i++)
		{
			i->second->acknowledged = true;
		}
		nodeMap.clear();
		frameMap.clear();
	}
}