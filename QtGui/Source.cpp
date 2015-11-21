/*
Authors: K D K Madusanka [kdk.madusanka@gmail.com]

Description:
This is the main source code for the "Adaptive Survellance Camera Networks" project.
All other suppotive functionalities are referenced.
The main program structure and multi-threading happening in here.

Log:
*/


#include <stdio.h>
#include <iostream>

#include <Windows.h> // threading purpose
#include <process.h>

#include <opencv2\highgui\highgui.hpp>	// open cv
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>

//#include "Graph.h"
//#include "Models.h"
#include "VideoProcessing.h"

unsigned int __stdcall threadForNode(void* data);

graph::Graph _graph;


int main(int argc, char* argv[])
{
	cout << "Advanced Surveillance Camera Network (ASCN)\nInitialting ...\n";

	cout << "Network Graph checking ...\n";

	_graph = graph::Graph();


	_graph.initGraph();

	if (!(_graph.isConfigured()))
	{
		// cofigure graph.
		vector<graph::ExitPoint> exitPointsList{ { 8, make_pair(20, 20), make_pair(50, 100) } };
		_graph.addNode(graph::Node("C001", "1.1.1.1", "GR1", exitPointsList));
		_graph.addNode(graph::Node("C002", "1.1.1.2", "GR2", exitPointsList));
		_graph.addNode(graph::Node("C003", "1.1.1.3", "GR3", exitPointsList));
		_graph.addNeighbour("C001", "C002", 8, 10);
		_graph.addNeighbour("C002", "C001", 2, 10);
		_graph.addNeighbour("C001", "C003", 6, 1);
		_graph.addNeighbour("C003", "C001", 4, 1);
	}


	// config graph with process ids - initialte threds and assign thred id to nodes in graph
	vector<string> nodeKeys = _graph.getKeysOfAllNodes();

	for (int i = 0; i < nodeKeys.size(); i++)
	{
		const char *s = nodeKeys[i].c_str();
		_beginthreadex(NULL, 0, &threadForNode, (void*)&(*s), 0, NULL);
	}

	system("pause");
	return 0;

}









#define drawCross( img, center, color, d )\
line(img, Point(center.x - d, center.y - d), Point(center.x + d, center.y + d), color, 2, CV_AA, 0);\
line(img, Point(center.x + d, center.y - d), Point(center.x - d, center.y + d), color, 2, CV_AA, 0 );


//struct PossibleProfilesMatchBundle
//{
//	vector<models::HumanBlob> *humanB;
//	vector<models::HumanBlob> *possibleP;
//};



unsigned int __stdcall threadForNode(void* data)
{
	char *nodeIdptr = static_cast<char*>(data);
	printf("THREAD [%d]:[%s]:: started.\n", GetCurrentThreadId(), &(*nodeIdptr));

	graph::Node *currentNodePtr = _graph.getNode(&(*nodeIdptr));

	currentNodePtr->ThreadId = GetCurrentThreadId();
	string videoLink = currentNodePtr->IP;
	vector<graph::ExitPoint> exitPoints = currentNodePtr->exitPoints;

	printf("%s :: %d :: %s \n", currentNodePtr->Id.c_str(), currentNodePtr->ThreadId, videoLink.c_str());

	// ###################################################
	//				opencv video tracking

	Mat frame;
	VideoCapture videoCapture(videoLink);
	vector<models::Blob> blobs, unidentifiedBlobs;
	vector<models::HumanBlob> humanBlobs, trackingHumanBlobs, possibleProfileList;
	vector<models::MissingHumanBlob> missingHumanBlobs;

	Mat drawing = Mat::zeros(frame.size(), CV_8UC1);

	VideoProcessing _vProcessing = VideoProcessing();

	if (!(videoCapture.read(frame)))
	{
		cerr << "Problem opening video source" << endl;
		return -1;
	}

	while (waitKey(10) != 27 && videoCapture.grab()) // terminate when ESC pressed
	{
		videoCapture.read(frame);
		if (frame.size().width > 1360 || frame.size().height > 760)
		{
			resize(frame, frame, Size(frame.size().width / 2, frame.size().height / 2));
		}

		// clear local vectors
		blobs.clear();
		unidentifiedBlobs.clear();
		humanBlobs.clear();


		// ***** should have update after map predicted and detected
		/////////

		// blob detection
		if (_vProcessing.BlobDetection(&frame, &blobs) == 0)
		{
			string x = currentNodePtr->Id.c_str();
			imshow(x, frame);
			continue;	// If no blobs detected continue while
		}

		if (trackingHumanBlobs.empty())	// if no human blobs tracked yet
		{
			unidentifiedBlobs = blobs;	// all blobs are unindentified
		}
		else	// if there are human blobs tracked in previous frames
		{
			// send &current_human_blobs_tracked and &blobs_detected_in_this_frame
			// and map existing human blobs with new set of blobs using GNN or Hungarian Algorithm and 
			// update &human_blobs as well as Profiles in central storage
			// missing blobs from data association goes to &unidentified_blobs
			// unmpped human blobs goes to &missing_human_blobs
			//mapPredictedWithCurrentPoints(&human_blobs, &blobs, &missing_human_blobs, &unidentified_blobs);
			// // with UpdatingKalmanForAllHumanObjects
			_vProcessing.DataAssociation(&blobs, &trackingHumanBlobs, &unidentifiedBlobs, &missingHumanBlobs);
		}

		if (!(unidentifiedBlobs.empty()))
		{
			_vProcessing.HumanDetection(&unidentifiedBlobs, &frame, &humanBlobs);
		}

		if (!(humanBlobs.empty()))
		{
			_vProcessing.CheckInProfiles(&humanBlobs, &possibleProfileList, &missingHumanBlobs, &trackingHumanBlobs);
		}

		if (!(humanBlobs.empty()))
		{
			_vProcessing.InitTrackingObject(&humanBlobs, &trackingHumanBlobs);
		}

		if (!(trackingHumanBlobs.empty()))
		{
			_vProcessing.KalmanCorrectAndPredict(&trackingHumanBlobs);
			_vProcessing.InformAdjecentNodes(&exitPoints, &trackingHumanBlobs);
			//_vProcessing.UpdateCentralProfiles(&trackingHumanBlobs);
		}







		//// get the moments
		//vector<Moments> mu(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	mu[i] = moments(human_blobs[i], false);
		//}

		//// get the mass centers:
		//vector<Point2f> mc(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		//}

		//for (size_t i = 0; i < mc.size(); i++)
		//{
		//	int selectedContourId = getReleventContour(mc[i]);

		//	Point measurePre(trackingObjectMap[selectedContourId].getLastPoint());
		//	vector<Point> pointsVector = trackingObjectMap[selectedContourId].addCenterPoint(mc[i]);
		//	Point measureCurrent(trackingObjectMap[selectedContourId].getLastPoint());

		//	drawCross(frame, measureCurrent, Scalar(0, 255, 0), 5);

		//	Mat prediction = trackingObjectMap[selectedContourId].kalmanPredict();
		//	Point kalmanPredict(prediction.at<float>(0), prediction.at<float>(1));

		//	Mat corrected = trackingObjectMap[selectedContourId].kalmanCorrect(mc[i]);
		//	Point kalmanCorrected(corrected.at<float>(0), corrected.at<float>(1));
		//	
		//	drawCross(frame, kalmanPredict, Scalar(0, 0, 255), 5);
		//	//drawCross(frame, kalmanCorrected, Scalar(0, 255, 255), 5);

		//	stringstream lbl;
		//	lbl << "Blob_" << selectedContourId;
		//	putText(frame, lbl.str(), measureCurrent, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 2);

		//	for (int i = pointsVector.size() - 1; i != 0; i--)
		//	{
		//		line(frame, pointsVector[i], pointsVector[i - 1], Scalar(200, 220, 80), 3);
		//	}
		//}

		//vector<vector<Point> > blobs_poly(human_blobs.size());
		//vector<Rect> boundRect(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	approxPolyDP(Mat(human_blobs[i]), blobs_poly[i], 3, true);
		//	boundRect[i] = boundingRect(Mat(blobs_poly[i]));
		//}

		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 0), 2, 8, 0);// scalar is for Bounding Box
		//}




		string strForImshow2 = currentNodePtr->Id.c_str();
		imshow(strForImshow2, frame);
	}
	// end opencv video tracking


	printf("\nNode %s::%d FINISHED \n", currentNodePtr->Id.c_str(), currentNodePtr->ThreadId);

	_endthreadex(0);
	return 0;
}
