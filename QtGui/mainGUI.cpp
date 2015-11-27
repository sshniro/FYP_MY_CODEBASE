#include <iostream>
#include "threadfornode.h"


int mainDEHAN(int argc, char* argv[])
{

	ThreadForNode* thread1 = new ThreadForNode();
	ThreadForNode* thread2 = new ThreadForNode();

	thread1->nodeId = "C001";
	thread2->nodeId = "C002";
	thread1->videoLink = "C:/Users/dehandecroos/Desktop/Videos/PRG6.avi";
	thread2->videoLink = "C:/Users/dehandecroos/Desktop/Videos/PRG29.avi";

	thread1->start();
	thread2->start();


	system("pause");
	return 0;
}