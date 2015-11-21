#include "videogeneration.h"
#include "qmessagebox.h"



VideoGeneration::VideoGeneration(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

VideoGeneration::~VideoGeneration()
{

}

vector<string> stringSplit(string s,string delimiter=" " ){

	vector<string> splittedStrings;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		//std::cout << token << std::endl;
		splittedStrings.push_back(token);
		s.erase(0, pos + delimiter.length());

	}
	splittedStrings.push_back(s);
	return splittedStrings;
}
void VideoGeneration::on_generateVideoPushButton_clicked()
{
	//string camPath = "C:\\Users\\dehandecroos\\Desktop\\Videos\\PRG28.avi";
	QString profileId = ui.profileName_lineEdit->text();
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
	stmt = con->createStatement();
	
	string cameraIds[] = { "camera_node_6", "camera_node_22", " camera_node_28" };
	int cameraIdsSize = sizeof(cameraIds) / sizeof(*cameraIds);
	string finalJoinQuery = "";
	int i = 1;
	for (string cameraId : cameraIds)
	{
		finalJoinQuery += "select * from " + cameraId + " where profile_id='" + profileId.toStdString() + "' ";
		if (i++ != cameraIdsSize) {
			finalJoinQuery += "union ";
		}
	}
	finalJoinQuery += "order by TimeStamp";
	
	struct CameraTimeStamp{
		string cameraId;
		string timestamp;
	};
	
	
	stmt->execute("USE camera");
	ResultSet *timeStampsForProfile = stmt->executeQuery(finalJoinQuery);
	//ResultSet *timeStampsForProfile = stmt->executeQuery("select * from camera_node_6 where profile_id = '1_6'");
	vector<CameraTimeStamp> timeStamps;
	
	while (timeStampsForProfile->next())
	{
		CameraTimeStamp timeStamp;
		timeStamp.cameraId = timeStampsForProfile->getString("Video_ID");
		timeStamp.timestamp = timeStampsForProfile->getString("TimeStamp");
		timeStamps.push_back(timeStamp);
	}

	
	vector<Mat> video;
	for (CameraTimeStamp ts : timeStamps)
	{
		string camPath = "C:\\Users\\dehandecroos\\Desktop\\Videos\\";
		string camId = ts.cameraId;
		camPath += "PRG" + camId + ".avi";
		VideoCapture cam;
		cam.open(camPath);
		int frameRate = cam.get(CV_CAP_PROP_FPS);
	
		vector<string> splittedStrings = stringSplit(ts.timestamp,".");
		int minutes = stoi(splittedStrings[0]);
		int seconds = stoi(splittedStrings[1]);
		int milliseconds = minutes * 60 + seconds * 1000;
		
		
		cam.set(CV_CAP_PROP_POS_MSEC, milliseconds);
		//namedWindow("Frame", 1);
		Mat frame;
		
		for (int frameCount = 0; frameCount < frameRate; frameCount++)
		{
			cam >> frame;
			//imshow("Frame", frame);
			
			int fontFace = FONT_HERSHEY_SIMPLEX;
			double fontScale = 1;
			int thickness = 3;
			cv::Point textOrg1(10, 50);
			putText(frame, "CAM:" + ts.cameraId, textOrg1, fontFace, fontScale, Scalar::all(250),2);
			cv::Point textOrg2(500, 50);
			//string frameC = "FRAME: " + to_string(frameCount);
			//putText(frame, frameC, textOrg2, fontFace, fontScale, Scalar::all(250), 2);
			//cvWaitKey(1);
			video.push_back(frame);
		}
		
		

		//VideoCapture

	}

	//for (;;){
		for (Mat frameZ : video)
		{
			QImage outImage((uchar*)frameZ.data,frameZ.cols,frameZ.rows,frameZ.step,QImage::Format_RGB888);
			//ui.lblOutput
			ui.lblOutput->setPixmap(QPixmap::fromImage(outImage));

			imshow(profileId.toStdString(), frameZ);
			cvWaitKey(1);
		}
	//}
	
	//QMessageBox Msgbox;
	//Msgbox.setText("The Profile ID : " + profileId);
	//Msgbox.exec();
}


/*

QString profileId = ui.profileName_lineEdit->text();

MySQL_Driver *driver;
Connection *con;
Statement *stmt;
driver = sql::mysql::get_mysql_driver_instance();
con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
stmt = con->createStatement();

string cameraIds[] = { "camera_node_6", "camera_node_22", " camera_node_28" };
int cameraIdsSize = sizeof(cameraIds) / sizeof(*cameraIds);
string finalJoinQuery = "";
int i = 1;
for (string cameraId : cameraIds)
{
finalJoinQuery += "select * from " + cameraId + " where profile_id='" + profileId.toStdString() + "' ";
if (i++ != cameraIdsSize) {
finalJoinQuery += "union ";
}
}
finalJoinQuery += "order by TimeStamp";

struct CameraTimeStamp{
string cameraId;
string timestamp;
};

//ResultSet *timeStampsForProfile = stmt->executeQuery(finalJoinQuery);
stmt->execute("USE camera");
ResultSet *timeStampsForProfile = stmt->executeQuery("select * from camera_node_6 where profile_id = '1_6'");
vector<CameraTimeStamp> timeStamps;

while (timeStampsForProfile->next())
{
CameraTimeStamp timeStamp;
timeStamp.cameraId = timeStampsForProfile->getString("Video_ID");
timeStamp.timestamp = timeStampsForProfile->getString("TimeStamp");
timeStamps.push_back(timeStamp);
}

string camPath = "C:\\Users\\dehandecroos\\Desktop\\Videos\\";
vector<Mat> video;
for (CameraTimeStamp ts : timeStamps)
{
string camId = ts.cameraId;
camPath += "PRG" + camId + ".avi";
VideoCapture cam;
cam.open(camPath);
vector<string> splittedStrings = stringSplit(ts.timestamp,".");
int minutes = stoi(splittedStrings[0]);
int seconds = stoi(splittedStrings[1]);
int milliseconds = minutes * 60 + seconds * 1000;

int frameRate = cam.get(CV_CAP_PROP_FPS);
cam.set(CV_CAP_PROP_POS_FRAMES, milliseconds);
Mat frame;
for (int frameCount = 0; frameCount < frameRate; frameCount++)
{
cam >> frame;
imshow("Frame", frame);
cvWaitKey(1);
video.push_back(frame);
}


//VideoCapture

}
QMessageBox Msgbox;
Msgbox.setText("The Profile ID : " + profileId);
Msgbox.exec();

*/