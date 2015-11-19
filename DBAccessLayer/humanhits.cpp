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