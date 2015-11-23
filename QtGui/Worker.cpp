#include "Worker.h"

Worker::Worker()
{
	qDebug() << "worker object created";
}

Worker::~Worker()
{
	qDebug() << "worker object deleted";
}

void Worker::process()
{
	qDebug() << "executing process function in QObject";
	emit finished();
}

void Worker::error(QString err)
{
	qDebug() << err;
}

void Worker::finished()
{
	qDebug() << "worker object finished";
}