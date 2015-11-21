#include "VideoProcessing.h"

VideoProcessing::VideoProcessing(){}

int VideoProcessing::BlobDetection(Mat *frame, vector<models::Blob> *outBlobs){
	blur(*frame, thresh_frame, Size(4, 4));   // blur ---
	backSubPtr->operator()(thresh_frame, thresh_frame, -1);  // background substraction
	morphologyEx(thresh_frame, thresh_frame, CV_MOP_CLOSE, morpho_ele);  // morphology pre processing
	threshold(thresh_frame, thresh_frame, 128, 255, CV_THRESH_BINARY);  // shadow removing, binary
	vector<vector<Point>> contours;
	findContours(thresh_frame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);  // inputFrame, output vector of blobs, retrieve external blobs, all px of each contour

	for each (vector<Point> con in contours)
	{
		(*outBlobs).push_back(models::Blob(con));
	}

	return (*outBlobs).size();
}

int VideoProcessing::HumanDetection(vector<models::Blob> *blobs, Mat *frame, vector<models::HumanBlob> *outHumanBlobs){
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


void VideoProcessing::DataAssociation(
	vector<models::Blob> *blobs,
	vector<models::HumanBlob> *trackingHumanBlobs,
	vector<models::Blob> *outUnidentifiedBlobs,
	vector<models::MissingHumanBlob> *outMissingHumanBlobs)
{
	vector<Mat> Predicted;
	vector<Point2f> Detected;
	vector<vector<int>> CostMetrix;



}

void VideoProcessing::CheckInProfiles(
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

void VideoProcessing::InitTrackingObject(vector<models::HumanBlob> *humanList, vector<models::HumanBlob> *trackingList)
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

void VideoProcessing::KalmanCorrectAndPredict(vector<models::HumanBlob> *trackingList)
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

void VideoProcessing::InformAdjecentNodes(vector<graph::ExitPoint> *exitsList, vector<models::HumanBlob> *trackingList)
{

}

VideoProcessing::~VideoProcessing(){}