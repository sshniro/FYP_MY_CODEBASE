#include "threadfornode.h"
#include "messagepasser.h"

ThreadForNode::ThreadForNode()
{
	msgPasser = new MessagePasser();
	connect(
		this, SIGNAL(sendProfileToNode(ProfileTransferObj, ThreadForNode*)), 
		msgPasser, SLOT(passMessage(ProfileTransferObj, ThreadForNode*))
		);
}

ThreadForNode::~ThreadForNode()
{

}

void ThreadForNode::run()
{
	VideoCapture cap(videoLink);

	while (cap.grab())
	{
		cap.read(frame);

		imshow(nodeId, frame);

		cvWaitKey(10);
	}

	qDebug() << "finished.";

	//emit sendProfileToNode(ProfileTransferObj, ThreadForNode*);
}

void ThreadForNode::updateProfileList(ProfileTransferObj profile)
{

}
