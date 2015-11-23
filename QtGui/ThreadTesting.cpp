#include "Thread_CameraNode.h"
#include <iostream>

int mainTT(int argc, char *argv[])
{
	Mat v1(100,100,CV_8UC3);
	Mat v2(100, 100, CV_8UC3);
	Mat v3(100, 100, CV_8UC3);
	QMutex mu;
	NodeThread* nThread1 = new NodeThread(&mu, &v1);
	NodeThread* nThread2 = new NodeThread(&mu, &v2);
	NodeThread* nThread3 = new NodeThread(&mu, &v3);

	nThread1->videoLink = "E:\\Final Year\\project\\human tracking\\coding\\Videos\\PRG6.avi";
	nThread2->videoLink = "E:\\Final Year\\project\\human tracking\\coding\\Videos\\PRG9.avi";
	nThread3->videoLink = "E:\\Final Year\\project\\human tracking\\coding\\Videos\\PRG23.avi";

	VideoCapture stream1(nThread1->videoLink);
	nThread1->stream = stream1;
	VideoCapture stream2(nThread2->videoLink);
	nThread2->stream = stream2;
	VideoCapture stream3(nThread3->videoLink);
	nThread3->stream = stream3;

	nThread1->start();
	nThread2->start();
	nThread3->start();

	while (true)
	{
		if (nThread1->isNotEnd && !(nThread1->isShown))
		{
			imshow("thread1", v1);
			nThread1->isShown = true;
		}
		if (nThread2->isNotEnd && !(nThread2->isShown))
		{
			imshow("thread2", v2);
			nThread2->isShown = true;
		}
		if (nThread3->isNotEnd && !(nThread3->isShown))
		{
			imshow("thread3", v3);
			nThread3->isShown = true;
		}
		cvWaitKey(1);

		if (!(nThread1->isNotEnd) && !(nThread2->isNotEnd) && !(nThread3->isNotEnd))
			break;
	}

	system("pause");
	return 0;
}