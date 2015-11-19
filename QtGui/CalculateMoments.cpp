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


void mainX(int argc, char *argv[])
{
	//QCoreApplication app(argc, argv);
	QApplication app(argc, argv);

	QStringList illegalFileTypes;
	illegalFileTypes << ".exe" << ".dll" << ".py" << ".jar" << ".au3" << ".lua" << ".msi";

	QString index = "C:\\Projects\\Output\\file1\\correct\\box\\";
	QString actual = "C:\\Projects\\Output\\file1\\correct\\";
	
	ManageBlobExtracts manageBlobExtracts;
	manageBlobExtracts.removeSmallFiles(index,actual);

	//MomentsCalculation moments;

	//moments.getAverageColourInConvexRegion();

	QDirIterator imgIt(index, QDir::Files);
	while (true)
	{
		if (!imgIt.hasNext())
			break;

		qDebug() << "Processing: " << imgIt.next();

		QFileInfo fileInfo = imgIt.fileInfo();
		QString box_file_Name = fileInfo.fileName();
		QString cmask_file_Name = fileInfo.fileName();
		cmask_file_Name.replace("_box_", "_cmask_");
		QString convex_file_Name = fileInfo.fileName();
		convex_file_Name.replace("_box_", "_convex_");

		QString hit_id = fileInfo.fileName();
		hit_id.replace("img_box_", " ");
		hit_id.replace(".jpg", " ");
		hit_id.trimmed();
		int hit_id_int = hit_id.toInt();


		QString pathBox = actual + box_file_Name;
		string pathBoxStr = pathBox.toStdString();
		Mat boxImage = imread((actual + box_file_Name).toStdString());
		Mat cmaskImage = imread((actual + cmask_file_Name).toStdString());
		Mat conImage = imread((actual + convex_file_Name).toStdString());

		//cvNamedWindow("boxImage",CV_WINDOW_NORMAL);
		//cvNamedWindow("cmaskImage", CV_WINDOW_NORMAL);
		//cvNamedWindow("conImage", CV_WINDOW_NORMAL);
		//imshow("boxImage", boxImage);
		//imshow("cmaskImage", cmaskImage);
		//imshow("conImage", conImage);

		cvtColor(cmaskImage, cmaskImage, CV_BGR2GRAY);
		double pixelCount  = 0;
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
	
		int boxHeight		= boxImage.rows;
		double ratio		= (double)boxHeight / (double)prop.height;
		int region1Height	= (int)(((double)prop.head) * ratio);
		int region2Height	= (int)(((double)prop.gait) * ratio);
		int region3Height	= (int)(((double)prop.leg)	* ratio);

		
		//Region(std::string id, int startRow, int startCol, int endRow, int endCol);
		string placement = "Top";
		Region region1(placement, 0, 0, region1Height, boxImage.cols);
		MomentCalculation2 mcalc;
		MomentAverage momentAverage1 =  mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region1);
		MomentStandardDeviation momentStandardDeviation1 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region1, &momentAverage1);
		MomentSkewness momentSkewness1 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region1,&momentAverage1);
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
		blob.addRegion(&region1);
		blob.addRegion(&region2);
		blob.addRegion(&region3);
		
		//qDebug() << "Tot 0 " << QString::number(tot0);
		//qDebug() << "Tot 1 " << QString::number(tot1);
		//qDebug() << "Tot 2 " << QString::number(tot2);
		//qDebug() << "AV 0 " << QString::number(tot0/pixelCount);
		//qDebug() << "AV 1 " << QString::number(tot1/pixelCount);
		//qDebug() << "AV 2 " << QString::number(tot2/pixelCount);

		//qDebug() << "stdDev0 0 " << QString::number(stdDev0);
		//qDebug() << "stdDev1 1 " << QString::number(stdDev1);
		//qDebug() << "stdDev2 2 " << QString::number(stdDev2);
		//qDebug() << "skew0 0 " << QString::number(skew0);
		//qDebug() << "skew1 1 " << QString::number(skew1);
		//qDebug() << "skew2 2 " << QString::number(skew2);

		HumanHits humanX;
		humanX.addHumanHit(&blob);

		//cvWaitKey(2000);
	}
	
	
	//return app.exec();
}