#include "VideoProcessing.h"

VideoProcessing::VideoProcessing(){}

int VideoProcessing::blobDetection(Mat frame, Ptr<BackgroundSubtractor> pMOG2, Mat mask, vector<models::Blob> *outBlobs){
	vector<vector<Point>> contours;
	contours = blbDetect.detectContours(frame, pMOG2, mask);
	for each (vector<Point> con in contours)
	{
		if (blbDetect.isQualifyingContour(con))
			(*outBlobs).push_back(models::Blob(con));
	}

	return (*outBlobs).size();
}

int VideoProcessing::humanDetection(vector<models::Blob> *blobs, Mat *frame, vector<models::HumanBlob> *outHumanBlobs){
	//update human blob set with the newly identified humans in the frame
	for (size_t i = 0; i < (*blobs).size(); i++)
	{
		if (contourArea((*blobs)[i].getContour()) > 100)
		{
			outHumanBlobs->push_back(models::HumanBlob(blobs->at(i)));
			blobs->erase(blobs->begin() + i);
		}
	}
	return (*outHumanBlobs).size();
}


void VideoProcessing::dataAssociation(
	vector<models::Blob> *blobs,
	vector<models::HumanBlob> *trackingHumanBlobs,
	vector<models::Blob> *outUnidentifiedBlobs,
	vector<models::MissingHumanBlob> *outMissingHumanBlobs)
{
	vector<Mat> Predicted;
	vector<Point2f> Detected;
	vector<vector<int>> CostMetrix;



}

void VideoProcessing::checkInProfiles(
	vector<models::HumanBlob> *humanList,
	vector<models::HumanBlob> *possibleList,
	vector<models::MissingHumanBlob> *missingList,
	vector<models::HumanBlob> *trackingList)
{
	// first check in possible profile list if not find in missing list
	// update the tracking list and possible list and missing list
	// send unidentified human list

	for (size_t i = 0; i < humanList->size(); i++)
	{
		trackingList->push_back(humanList->at(i));
	}
}

void VideoProcessing::initTrackingObject(vector<models::HumanBlob> *humanList, vector<models::HumanBlob> *trackingList)
{
	bool temp = false;
	for (size_t i = 0; i < humanList->size(); i++)
	{
		for (size_t j = 0; j < trackingList->size(); j++)
		{
			if (humanList->at(i) == trackingList->at(j))
			{
				temp = true;
				continue;
			}
		}
		if (!temp)
		{
			trackingList->push_back(humanList->at(i));
		}
		temp = false;
	}
}

void VideoProcessing::kalmanCorrectAndPredict(vector<models::HumanBlob> *trackingList)
{
	Mat_<float> mesurement(2, 1);
	mesurement.setTo(Scalar(0));
	Point temp;
	for (size_t i = 0; i < trackingList->size(); i++)
	{
		// Kalman Correct
		temp = trackingList->at(i).centerPointList.back();
		mesurement(0) = temp.x;
		mesurement(1) = temp.y;
		trackingList->at(i).kalmanFilter.correct(mesurement);
		mesurement.empty();

		// Kalman Predict
		trackingList->at(i).kalmanFilter.predict();
	}
}

void VideoProcessing::informAdjecentNodes(vector<graph::ExitPoint> *exitsList, vector<models::HumanBlob> *trackingList)
{

}

VideoProcessing::~VideoProcessing(){}