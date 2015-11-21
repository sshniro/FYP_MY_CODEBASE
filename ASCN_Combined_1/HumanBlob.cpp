#include "Models.h"

using namespace models;

HumanBlob::HumanBlob(){};

HumanBlob::HumanBlob(models::Blob superBlob)
{
	blob = superBlob;

	Point2f mc = blob.getmassCenter();

	centerPointList.push_back(mc);

	KalmanFilter KF(4, 2, 0);

	KF.statePre.at<float>(0) = 0;
	KF.statePre.at<float>(1) = 0;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;

	KF.statePost.at<float>(0) = mc.x;
	KF.statePost.at<float>(1) = mc.y;
	KF.statePost.at<float>(2) = 0;
	KF.statePost.at<float>(3) = 0;

	KF.transitionMatrix = *(Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1); // Including velocity

	KF.processNoiseCov = *(cv::Mat_<float>(4, 4) << 0.2, 0, 0.2, 0, 0, 0.2, 0, 0.2, 0, 0, 0.3, 0, 0, 0, 0, 0.3);

	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF.errorCovPost, Scalar::all(.1));

	kalmanFilter = KF;
	
}

bool HumanBlob::operator==(const HumanBlob& human)
{
	if (this->profileID == human.profileID)
		return true;
	else
		return false;
}

HumanBlob::~HumanBlob(){};