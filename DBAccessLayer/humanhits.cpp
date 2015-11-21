#include "dbaccesslayer_global.h"
#include "humanhits.h"


using namespace sql;
using namespace mysql;
using namespace std;


void HumanHits::addHumanHit(string id, string path, string hit_id, double av0, double av1, double av2, double stdDev0, double stdDev1, double stdDev2, double skew0, double skew1, double skew2)
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");


	QString insertQuery_p1 = "INSERT INTO human_hits(img_id,path,av0,av1,av2,stdDev0,stdDev1,stdDev2,skew0,skew1,skew2,hit_id) VALUES(";
	QString insertQuery_p2 =
		QString("'") +
		QString::fromStdString(id)
		+ QString("','")
		+ QString::fromStdString(path) + QString("',")
		+ QString::number(av0) + QString(",")
		+ QString::number(av1) + QString(",")
		+ QString::number(av2) + QString(",")
		+ QString::number(stdDev0) + QString(",")
		+ QString::number(stdDev1) + QString(",")
		+ QString::number(stdDev2) + QString(",")
		+ QString::number(av0) + QString(",")
		+ QString::number(av1) + QString(",")
		+ QString::number(av2) + QString(",")
		+ QString("0")
		+ QString(")");

	QString finalQuery = insertQuery_p1 + insertQuery_p2;
	string stdString = finalQuery.toStdString();

	stmt->execute(stdString);
	delete con;
	delete stmt;


}

void HumanHits::addHumanHit(Blob *blob)
{

	for (auto &region : blob->getAllRegions()) // access by reference to avoid copying
	{
		
		HumanHits hh;
		hh.addHumanHit(blob->hitId, region.regionId, region.getAverageMoment(), region.getStandardDeviationMoment(), region.getSkewnessMoment());


		//addHumanHit(blob.id+"_"+region.id,"",blob.id,)
	}

	

}


void HumanHits::addHumanHit(string hitId, string regionId, MomentAverage *momentAverage, MomentStandardDeviation *momentStandardDeviation, MomentSkewness *momentSkewness)
{
	string id = hitId + "_" + regionId;
	addHumanHit(
	id,
	"",
	hitId,
	momentAverage->channel0,
	momentAverage->channel1,
	momentAverage->channel2,
	momentStandardDeviation->channel0,
	momentStandardDeviation->channel1,
	momentStandardDeviation->channel2,
	momentSkewness->channel0,
	momentSkewness->channel1,
	momentSkewness->channel2);


	


}


HumanHits::HumanHits()
{
	
	

}

HumanHits::HumanHits(MySQL_Driver *driver, Connection *con)
{
	driver = driver;
	con = con;

}
HumanHits::~HumanHits()
{

}

vector<string> stringSplit(string s, string delimiter = " "){

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

vector<Profile> HumanHits::getAllProfilesInSecond(string absoluteTime, string cameraNode)
{
	vector<Profile> profiles;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");
	string query = "select profile_id, timestamp  from " + cameraNode +" where TimeStamp = "+ absoluteTime;
	// select profile_id, timestamp from camera_node_22 where TimeStamp = 1.54;
	ResultSet *profileResult = stmt->executeQuery(query);
	while (profileResult->next())
	{
		Profile prf;
		prf.profileId = profileResult->getString("profile_id");
		vector<string> coord = stringSplit(profileResult->getString("timestamp"),",");
		prf.centreX = stoi(coord[0]);
		prf.centreY = stoi(coord[1]);
		profiles.push_back(prf);
	}

	delete con;
	delete stmt;

	return profiles;

}