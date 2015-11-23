//#include <iostream>

#include "QtCore\qthread.h"
#include "QtCore\qmutex.h"
#include "qdebug.h"

//#include <opencv2\core\core.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
//#include <opencv2\video\tracking.hpp>
//#include <opencv2\video\background_segm.hpp>
//#include <opencv2\highgui\highgui.hpp>

//using namespace cv;
//using namespace std;

class Worker : public QObject
{
public:
	Worker();
	~Worker();

	public slots:
	void process();

signals:
	void finished();
	void error(QString err);

private:

};