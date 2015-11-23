#ifndef WORKER2_H
#define WORKER2_H

#include <QObject>
#include "QtCore\qthread.h"
#include "QtCore\qmutex.h"
#include "qdebug.h"

class Worker2 : public QObject
{
	Q_OBJECT

public:
	Worker2(QObject *parent = 0);
	~Worker2();

public slots:
	void process();

signals:
	void finished();

private:

};

#endif // WORKER2_H
