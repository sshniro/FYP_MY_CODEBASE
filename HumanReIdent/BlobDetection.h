#ifndef BLOBDETECTION_H
#define BLOBDETECTION_H

#include "humanreident_global.h"

#include "opencv2/core/core.hpp"
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>


using namespace cv;
using namespace std;
class HUMANREIDENT_EXPORT BlobDetection
{
public:

	vector<vector<Point>> detectContours(Mat frame, Ptr< BackgroundSubtractor>& pMOG2, Mat& fgMaskMOG2);
	bool BlobDetection::isQualifyingContour(vector<Point> contour);
	vector<vector<Point>> detectEnclosingConvexHull(vector< vector< Point> >  contours);
	BlobDetection();
	~BlobDetection();


};

#endif 

