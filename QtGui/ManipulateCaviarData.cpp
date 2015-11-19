#include <QtCore\qcoreapplication.h>
#include <QtCore\QDirIterator>
#include <QtCore\QDir>
#include <QtCore\QDebug>
#include <QtCore\QFileInfo>
#include <QtCore\QStringList>
#include <QApplication>
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <ManageBlobExtracts.h>
#include "MomentCalculation2.h"
#include <humanhits.h>
#include <caviar_hits.h>


using namespace cv;
using namespace std;
struct ColorMoments{
	double ch1Av;
	double ch2Av;
	double ch3Av;

	double ch1stdDev;
	double ch2stdDev;
	double ch3stdDev;

	double ch1Sk;
	double ch2Sk;
	double ch3Sk;
};

struct HumanProportions{
	int height = 14;
	int head = 2;
	int gait = 5;
	int leg = 7;

	int currentHeight;
	int currentHead;
	int currentGait;
	int currentLeg;

};


void main(int argc, char *argv[])
{
	//QCoreApplication app(argc, argv);
	QApplication app(argc, argv);
	caviar_hits cc;
	cc.compareAllHits();

	
		//std::auto_ptr< sql::PreparedStatement > prep_stmt(con->prepareStatement("SELECT id, label FROM test ORDER BY id ASC"));
		//std::auto_ptr< sql::ResultSet > res(prep_stmt->executeQuery());




	
}