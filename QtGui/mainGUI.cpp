#include <iostream>
#include "threadfornode.h"


int main(int argc, char* argv[])
{

	ThreadForNode* thread1 = new ThreadForNode();
	ThreadForNode* thread2 = new ThreadForNode();

	thread1->nodeId = "C001";
	thread2->nodeId = "C002";
	thread1->videoLink = "E:/Final Year/project/human tracking/coding/Videos/PRG6.avi";
	thread2->videoLink = "E:/Final Year/project/human tracking/coding/Videos/PRG9.avi";

	thread1->start();
	thread2->start();


	system("pause");
	return 0;
}