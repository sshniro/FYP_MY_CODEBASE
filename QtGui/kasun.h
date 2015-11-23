#ifndef KASUN_H
#define KASUN_H

#include <QObject>

#include "QtCore\qthread.h"
#include "QtCore\qmutex.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "Worker2.h"

class Kasun : public QObject
{
	Q_OBJECT

public:
	Kasun(QObject *parent =0);
	~Kasun();

	void threadsInit();

private:
	
};

#endif // KASUN_H
