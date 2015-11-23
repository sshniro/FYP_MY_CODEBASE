#include "kasun.h"

Kasun::Kasun(QObject *parent)
	: QObject(parent)
{

}

Kasun::~Kasun()
{

}


void Kasun::threadsInit()
{
	QThread* thread1 = new QThread();
	Worker2* worker = new Worker2();
	worker->moveToThread(thread1);

	// connects the thread’s started() signal to the processing() slot in the worker, causing it to start.
	connect(thread1, SIGNAL(started()), worker, SLOT(process()));
	// when the worker instance emits finished(),it will signal the thread to quit, i.e. shut down.
	connect(worker, SIGNAL(finished()), thread1, SLOT(quit()));
	// mark the worker instance using the same finished() signal for deletion.
	connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
	// this will cause the thread to be deleted only after it has fully shut down.
	connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));

	thread1->start();
}