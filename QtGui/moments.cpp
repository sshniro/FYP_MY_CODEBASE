
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>

using namespace cv;
using namespace std;

int calc_mean(Mat imgchannel);


int mainxc(int argc, char** argv)
{



	//Mat image;
	
	string number = "";
	int count = 0;
	

	Mat img_convex;
	Mat img_cmask;
	Mat img_box;
	string windowName1 = "img_convex";
	string windowName2 = "img_cmask";
	string windowName3 = "img_box";
	IplImage *desimg, *srcimg;
	char link[512];
	//Remove Small Images
	for (int i = 1; i < 3294; i++)
	{


		string number = "";

		if (count < 10){
			number = "000" + to_string(i);

		}
		else if (count < 100){
			number = "00" + to_string(i);
		}
		else if (count < 1000){
			number = "0" + to_string(i);
		}
		else{
			number = to_string(i);
		}
		//C:\Projects\Output\file1\correct
		string img_convex_str = "C:\\Projects\\Output\\file1\\correct\\img_convex_" + number + ".jpg";
		string img_cmask_str = "C:\\Projects\\Output\\file1\\correct\\img_cmask_" + number + ".jpg";
		string img_box_str = "C:\\Projects\\Output\\file1\\correct\\img_box_" + number + ".jpg";
		char img_convex_ch[512];
		char img_cmask_ch[512];
		char img_box_ch[512];
		strcpy(img_convex_ch, img_convex_str.c_str());
		strcpy(img_cmask_ch, img_cmask_str.c_str());
		strcpy(img_box_ch, img_box_str.c_str());


		IplImage *img_convex_ipl = cvLoadImage(img_box_ch);
		IplImage *img_cmask_ipl = cvLoadImage(img_cmask_ch);
		IplImage *img_box_ipl = cvLoadImage(img_box_ch);

		cout << img_convex_ipl->imageSize << endl;
		cout << img_cmask_ipl->imageSize << endl;
		cout << img_box_ipl->imageSize << endl;

		cvShowImage("imgC", img_convex_ipl);
		cvShowImage("imgM", img_cmask_ipl);
		cvShowImage("imgB", img_box_ipl);

		cvWaitKey(0);


	}

	for (;;)
	{

		namedWindow(windowName1, CV_WINDOW_NORMAL);
		namedWindow(windowName2, CV_WINDOW_NORMAL);
		namedWindow(windowName3, CV_WINDOW_NORMAL);
		if (count < 10){
			number = "000" + to_string(count);

		}
		else if (count < 100){
			number = "00" + to_string(count);
		}
		else if (count < 1000){
			number = "0" + to_string(count);
		}
		else if (count>1300)
		{
			break;
		}
		else{
			number = to_string(count);
		}
		count++;
		IplImage *image = cvLoadImage(argv[1]);

		//sequence >> image;
		string img_convex_str		= "C:\\Projects\\Output\\file1\\correct\\img_convex_" + number + ".jpg";
		string img_cmask_str = "C:\\Projects\\Output\\file1\\c2\\img_cmask_" + number + ".jpg";
		string img_box_str = "C:\\Projects\\Output\\file1\\c2\\img_box_" + number + ".jpg";

		//image.release();
		img_convex = imread(img_convex_str);
		img_cmask = imread(img_cmask_str);
		img_box = imread(img_box_str);


		//windowName = number;
		
		cout << number << endl;
		if (img_box_str.empty())
		{
			cout << "End of Sequence" << endl;
			continue;
		}




		imshow(windowName1, img_box);
		imshow(windowName2, img_cmask);
		imshow(windowName3, img_convex);


		cvWaitKey(4000);
	}

	return 0;
}


