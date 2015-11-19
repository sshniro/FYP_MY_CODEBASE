#include "stdafx.h"
#include "MomentsCalculation.h"

MomentsCalculation::MomentsCalculation(QObject *parent)
	: QObject(parent)
{
	
}

MomentsCalculation::~MomentsCalculation()
{

}

MomentAverage MomentsCalculation::getAverageColourInConvexRegion(Mat image, Mat imageMask, Region region)
{
	int pixelCount = 0;
	int startRow	= region.startRow;
	int endRow		= region.endRow;
	int startCol	= region.startCol;
	int endCol		= region.endCol;
	int tot0 = 0;
	int tot1 = 0;
	int tot2 = 0;
	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;
				
				tot0 += image.at<cv::Vec3b>(i, j)[0];
				tot1 += image.at<cv::Vec3b>(i, j)[1];
				tot2 += image.at<cv::Vec3b>(i, j)[2];

			}
		}
	}

	double av0 = (double)tot0 / (double)pixelCount;
	double av1 = (double)tot1 / (double)pixelCount;
	double av2 = (double)tot2 / (double)pixelCount;
	MomentAverage momentAverage(av0,av1,av2);
	
	return momentAverage;


}

MomentStandardDeviation MomentsCalculation::getStandardDeviationInConvexRegion(Mat image, Mat imageMask, Region region, MomentAverage momentAverage)
{
	int pixelCount = 0;
	int startRow	=	region.startRow;
	int endRow		=	region.endRow;
	int startCol	=	region.startCol;
	int endCol		=	region.endCol;

	double av0 = momentAverage.channel0;
	double av1 = momentAverage.channel1;
	double av2 = momentAverage.channel2;

	double varSquareTot0 = 0;
	double varSquareTot1 = 0;
	double varSquareTot2 = 0;

	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;

				double original0 = image.at<cv::Vec3b>(i, j)[0];
				double original1 = image.at<cv::Vec3b>(i, j)[1];
				double original2 = image.at<cv::Vec3b>(i, j)[2];

				varSquareTot0 += pow(av0 - original0, 2);
				varSquareTot1 += pow(av1 - original1, 2);
				varSquareTot2 += pow(av2 - original2, 2);

			}
		}
	}

	double stdDev0 = varSquareTot0 / pixelCount;
	double stdDev1 = varSquareTot1 / pixelCount;
	double stdDev2 = varSquareTot2 / pixelCount;

	stdDev0 = pow(stdDev0, 0.5);
	stdDev1 = pow(stdDev0, 0.5);
	stdDev2 = pow(stdDev0, 0.5);
	MomentStandardDeviation momentStandardDeviation(stdDev0, stdDev1, stdDev2);

	return momentStandardDeviation;

}
MomentSkewness MomentsCalculation::getSkewnessnInConvexRegion(Mat image, Mat imageMask, Region region, MomentAverage momentAverage)
{
	int pixelCount = 0;
	int startRow	= region.startRow;
	int endRow		= region.endRow;
	int startCol	= region.startCol;
	int endCol		= region.endCol;

	double av0 = momentAverage.channel0;
	double av1 = momentAverage.channel1;
	double av2 = momentAverage.channel2;

	int tot0 = 0;
	int tot1 = 0;
	int tot2 = 0;

	double varCubeTot0 	 =0; 
	double varCubeTot1 	 =0; 
	double varCubeTot2 	 =0; 
	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;

				double original0 = image.at<cv::Vec3b>(i, j)[0];
				double original1 = image.at<cv::Vec3b>(i, j)[1];
				double original2 = image.at<cv::Vec3b>(i, j)[2];


				varCubeTot0 += pow(av0 - original0, 3);
				varCubeTot1 += pow(av1 - original1, 3);
				varCubeTot2 += pow(av2 - original2, 3);

			}
		}
	}
	double skew0 = varCubeTot0 / pixelCount;
	double skew1 = varCubeTot1 / pixelCount;
	double skew2 = varCubeTot2 / pixelCount;
	skew0 = cbrt(skew0);
	skew1 = cbrt(skew1);
	skew2 = cbrt(skew2);
	MomentSkewness momentSkewness(skew0, skew1, skew2);

	return momentSkewness;
}