#include "threadfornode.h"
#include "messagepasser.h"

ThreadForNode::ThreadForNode()
{
	msgPasser = new MessagePasser();
	acknowledged = true;
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
		
		// process here

		// end process here

		waitForAcknowledge();
		QImage outImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
		int x = outImage.byteCount();
		emit sendFrameToMain(outImage, this);

		this->acknowledged = false;
	}

	qDebug() << "finished.";

	//emit sendProfileToNode(ProfileTransferObj, ThreadForNode*);
}

void ThreadForNode::updateProfileList(ProfileTransferObj profile)
{

}


void ThreadForNode::waitForAcknowledge()
{
	while (!acknowledged);
}