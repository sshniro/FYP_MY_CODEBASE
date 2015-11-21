#include "Models.h"

using namespace models;

TrackingObject::TrackingObject(){}

TrackingObject::TrackingObject(Point initCenterPoint, vector<Point> initContour)
{
	centerPoint.push_back(initCenterPoint);
	contour = initContour;
	paneltyIndex = 0;

	KalmanFilter KF(4, 2, 0);

	KF.statePre.at<float>(0) = 0;
	KF.statePre.at<float>(1) = 0;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;

	KF.statePost.at<float>(0) = initCenterPoint.x;
	KF.statePost.at<float>(1) = initCenterPoint.y;
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

vector<Point> TrackingObject::addCenterPoint(Point p)
{
	centerPoint.push_back(p);
	if (centerPoint.size() > 10)
		centerPoint.erase(centerPoint.begin(), centerPoint.end() - 5);
	return centerPoint;
}

Point TrackingObject::getLastPoint()
{
	return centerPoint[centerPoint.size() - 1];
}

Mat TrackingObject::kalmanPredict()
{
	return kalmanFilter.predict();
}

Mat TrackingObject::kalmanCorrect(Point p)
{
	Mat_<float> measurement(2, 1);
	measurement.setTo(Scalar(0));
	measurement(0) = p.x;
	measurement(1) = p.y;
	return kalmanFilter.correct(measurement);
}

TrackingObject::~TrackingObject(){}