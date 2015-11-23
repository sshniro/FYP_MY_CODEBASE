#include "worker2.h"

Worker2::Worker2(QObject *parent)
	: QObject(parent)
{
	qDebug() << "worker object created";
}

Worker2::~Worker2()
{
	qDebug() << "worker object deleted";
}

void Worker2::process()
{
	qDebug() << "executing process function in QObject";
	emit finished();
}