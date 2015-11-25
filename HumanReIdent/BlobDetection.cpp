#include "stdafx.h"

#include "humanreident.h"

#include "BlobDetection.h"



BlobDetection::BlobDetection()
{

}


BlobDetection::~BlobDetection()
{
}

vector< vector< Point> > BlobDetection::detectContours(Mat frame, Ptr< BackgroundSubtractor>& pMOG2Pointer , Mat& fgMaskMOG2)
{
	vector< vector< Point> > result;
	imshow("Inside Library Frame",frame);
	cvWaitKey(1);

	Mat fgMaskMOG2X = fgMaskMOG2.clone(); 

	Mat ContourImg; 
	Ptr< BackgroundSubtractor> pMOG2 = pMOG2Pointer; 
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));


	//PreProcess
	blur(frame, frame, Size(4, 4));

	//Background subtraction
	pMOG2->operator()(frame, fgMaskMOG2X, -1);
	morphologyEx(fgMaskMOG2X, frame, CV_MOP_CLOSE, element);
	imshow("ShadowNotRemoved", frame);
	//imshow("Testing 0", frame);
	//threshold(frame, frame, 100, 180, CV_THRESH_BINARY);

	imshow("ShadowRemoved", frame);
	//Find contour
	ContourImg = frame.clone();
	//imshow("Testing 1", frame);
	cvWaitKey(1);
	findContours(ContourImg,
		result, // a vector of contours
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // all pixels of each contours


	fgMaskMOG2 = fgMaskMOG2X.clone();
	return result;
}

bool BlobDetection::isQualifyingContour(vector<Point> contour)
{ 
	bool result = false;
	int minimum_width = 30;//30;
	int maximum_width = 180;//100;
	int minimum_height = 30;// 30;
	double minimum_htow_ratio = 1.3;
	Rect roi = boundingRect(contour);
	double heightToWidthRatio = static_cast<double>(roi.height) / static_cast<double>(roi.width);
	if (	roi.width			>	minimum_width	&&
			roi.width			<	maximum_width	&&
			roi.height			>	minimum_height	&&
			heightToWidthRatio	>	minimum_htow_ratio
		)
	{
		result = true;
	}

	return result;
	

}

vector< vector< Point> > BlobDetection::detectEnclosingConvexHull(vector<vector<Point>> contours)
{
	vector< vector< Point> > hull;
	return hull;
}