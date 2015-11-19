#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;
using namespace cv;

namespace models
{
//#ifndef TrackingObject_HEADER
//#define TrackingObject_HEADER
	class TrackingObject
	{
	public:
		vector<Point> contour;
		TrackingObject();
		TrackingObject(Point initCenterPoint, vector<Point> initContour); // initialize center points vector and kalman object from initial center point
		~TrackingObject();

		vector<Point> addCenterPoint(Point p); // add new point to the end of Point vector and returns new vector<Point>
		Point getLastPoint(); // get the last point of the vector
		Mat kalmanPredict(); // call predict function for the internal kalman object
		Mat kalmanCorrect(Point p); // call correct function for the internal kalman object

	protected:
		vector<Point> centerPoint; // list of center points (5 of history and current)
		KalmanFilter kalmanFilter; // kalman filter object for the current human blob
		int paneltyIndex; // count of consecutive frames that blob doesn't appear
	};
//#endif

//#ifndef Blob_HEADER
//#define Blob_HEADER
	class Blob
	{
	public:
		Blob();
		Blob(vector<Point> _contour);

		vector<Point> getContour();
		Moments getMoments();
		Point2f getmassCenter();

		void setContour(vector<Point> _contour);

		~Blob();
	protected:
		vector<Point> contour;
		Moments mu;
		Point2f mc;
	};
//#endif

//#ifndef HumanBlob_HEADER
//#define HumanBlob_HEADER
	class HumanBlob
	{
	public:
		HumanBlob();
		HumanBlob(models::Blob superBlob);
		~HumanBlob();
	
		Blob blob;
		vector<Point> centerPointList;
		KalmanFilter kalmanFilter;
		int profileID;
	};
//#endif

//#ifndef MissingHunamBlob_HEADER
//#define MissingHunamBlob_HEADER
	class MissingHumanBlob
	{
	public:
		MissingHumanBlob();
		MissingHumanBlob(models::HumanBlob superHumanBlob);
		~MissingHumanBlob();
	
		HumanBlob humanBlob;
		time_t missedTime;
	};
//#endif
}