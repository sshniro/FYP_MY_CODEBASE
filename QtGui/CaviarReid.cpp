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


void mainJ(int argc, char *argv[])
{
	//QCoreApplication app(argc, argv);
	QApplication app(argc, argv);

	QStringList illegalFileTypes;
	illegalFileTypes << ".exe" << ".dll" << ".py" << ".jar" << ".au3" << ".lua" << ".msi";

	QString index = "H:\\Datasets\\CAVIAR4REID\\CAVIARa\\";
	//QString actual = "C:\\Projects\\Output\\file1\\correct\\";
	//H:\\Datasets\\CAVIAR4REID\\CAVIARa\\
	ManageBlobExtracts manageBlobExtracts;
	//manageBlobExtracts.removeSmallFiles(index, actual);

	//MomentsCalculation moments;

	//moments.getAverageColourInConvexRegion();

	QDirIterator imgIt(index, QDir::Files);
	while (true)
	{
		if (!imgIt.hasNext())
			break;
		qDebug() << imgIt.next();
		QFileInfo fileInfo = imgIt.fileInfo();
		QString box_file_Name = fileInfo.fileName();

		Mat boxImage = imread((index + box_file_Name).toStdString());
		Mat cmaskImage(boxImage.rows, boxImage.cols, CV_8UC1,Scalar(255));


		QStringRef personIdString(&box_file_Name ,2,2);
		QStringRef hitIdXString(&box_file_Name, 4, 3);
		int humanId = personIdString.toInt();
		int hitIdX = hitIdXString.toInt();
		qDebug() << humanId << "";
		qDebug() << hitIdX << endl;

		//cvtColor(boxImage, cmaskImage, CV_BGR2GRAY);
		double pixelCount = 0;
		double region1tot0 = 0;
		double region1tot1 = 0;
		double region1tot2 = 0;
		double region2tot0 = 0;
		double region2tot1 = 0;
		double region2tot2 = 0;
		double region3tot0 = 0;
		double region3tot1 = 0;
		double region3tot2 = 0;


		//Average
		HumanProportions prop;

		int boxHeight = boxImage.rows;
		double ratio = (double)boxHeight / (double)prop.height;
		int region1Height = (int)(((double)prop.head) * ratio);
		int region2Height = (int)(((double)prop.gait) * ratio);
		int region3Height = (int)(((double)prop.leg)	* ratio);


		//Region(std::string id, int startRow, int startCol, int endRow, int endCol);
		string placement = "Top";
		Region region1(placement, 0, 0, region1Height, boxImage.cols);
		MomentCalculation2 mcalc;
		MomentAverage momentAverage1 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region1);
		MomentStandardDeviation momentStandardDeviation1 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region1, &momentAverage1);
		MomentSkewness momentSkewness1 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region1, &momentAverage1);
		region1.setMoments(&momentAverage1, &momentStandardDeviation1, &momentSkewness1);


		placement = "Middle";
		Region region2(placement, 0, 0, region2Height, boxImage.cols);
		MomentAverage momentAverage2 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region2);
		MomentStandardDeviation momentStandardDeviation2 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region2, &momentAverage2);
		MomentSkewness momentSkewness2 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region2, &momentAverage2);
		region2.setMoments(&momentAverage2, &momentStandardDeviation2, &momentSkewness2);

		placement = "Bottum";
		Region region3(placement, 0, 0, region3Height, boxImage.cols);
		MomentAverage momentAverage3 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region3);
		MomentStandardDeviation momentStandardDeviation3 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region3, &momentAverage3);
		MomentSkewness momentSkewness3 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region3, &momentAverage3);
		region3.setMoments(&momentAverage3, &momentStandardDeviation3, &momentSkewness3);

		string id = box_file_Name.toStdString();
		Blob blob(id, boxImage.rows, boxImage.cols);
		blob.human_id_actual = to_string(humanId);
		blob.addRegion(&region1);
		blob.addRegion(&region2);
		blob.addRegion(&region3);

		caviar_hits cc;
		cc.addCaviarHit(&blob);

	}
}