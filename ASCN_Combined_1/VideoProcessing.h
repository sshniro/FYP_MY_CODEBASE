#include <opencv2\highgui\highgui.hpp>	// open cv
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include "Models.h"
#include "Graph.h"

// blob detection
// in	: *frame
// out	: contours

// human detection
// in	: *contours, *frame
// out	: filtered_contours

// kalman filtering

// comparison algo (get relevent contours)

using namespace std;
using namespace cv;


class VideoProcessing
{
public:
	VideoProcessing();
	int BlobDetection(Mat *frame, vector<models::Blob> *outBlobs);
	int HumanDetection(vector<models::Blob> *blobs, Mat *frame, vector<models::HumanBlob> *outHumanBlobs);

	void DataAssociation(
		vector<models::Blob> *blobs, 
		vector<models::HumanBlob> *trackingHumanBlobs, 
		vector<models::Blob> *outUnidentifiedBlobs,
		vector<models::MissingHumanBlob> *outMissingHumanBlobs);

	void CheckInProfiles(
		vector<models::HumanBlob> *humanList, 
		vector<models::HumanBlob> *possibleList, 
		vector<models::MissingHumanBlob> *missingList, 
		vector<models::HumanBlob> *trackingList);

	void InitTrackingObject(vector<models::HumanBlob> *humanList, vector<models::HumanBlob> *trackingList);

	void KalmanCorrectAndPredict(vector<models::HumanBlob> *trackingList);

	void InformAdjecentNodes(vector<graph::ExitPoint> *exitsList, vector<models::HumanBlob> *trackingList);

	~VideoProcessing();

private:
	Mat thresh_frame;
	Ptr<BackgroundSubtractor> backSubPtr = new BackgroundSubtractorMOG2(300, 32, true);
	Mat morpho_ele = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));

protected:

};