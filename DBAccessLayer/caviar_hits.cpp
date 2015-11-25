#include "caviar_hits.h"


caviar_hits::caviar_hits()
{
}



caviar_hits::~caviar_hits()
{
}

void caviar_hits::addCaviarHit(string img_id, int region_id, int human_id_actual, double av0, double av1, double av2, double stdDev0, double stdDev1, double stdDev2, double skew0, double skew1, double skew2)
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");

	//Part I
	//Check if picture exists
	string tryGetCurrentImageQuery = "SELECT * FROM caviar_hits WHERE img_id = '" + img_id + "'";
	std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(tryGetCurrentImageQuery));
	if (res->rowsCount() == 0)
	{
		QString insertImgQuery_p1 = "INSERT INTO caviar_hits(img_id,human_id_actual) VALUES(";
		QString insertImgQuery_p2 =
			QString("'") +
			QString::fromStdString(img_id)
			+ QString("',")
			+ QString::number(human_id_actual)
			+ QString(")");

		QString insertImgQuery = insertImgQuery_p1 + insertImgQuery_p2;
		string insertImgQueryStdString = insertImgQuery.toStdString();
		stmt->execute(insertImgQueryStdString);
	}



	//Part II
	QString insertMomentQuery_p1 = "INSERT INTO moments(img_id,region_id,av0,av1,av2,stdDev0,stdDev1,stdDev2,skew0,skew1,skew2) VALUES(";
	QString insertMomentQuery_p2 =
		QString("'") +
		QString::fromStdString(img_id)
		+ QString("',")
		+ QString::number(region_id) + QString(",")
		+ QString::number(av0) + QString(",")
		+ QString::number(av1) + QString(",")
		+ QString::number(av2) + QString(",")
		+ QString::number(stdDev0) + QString(",")
		+ QString::number(stdDev1) + QString(",")
		+ QString::number(stdDev2) + QString(",")
		+ QString::number(av0) + QString(",")
		+ QString::number(av1) + QString(",")
		+ QString::number(av2)
		+ QString(")");

	QString insertMomentQuery = insertMomentQuery_p1 + insertMomentQuery_p2;
	string insertMomentQueryStdString = insertMomentQuery.toStdString();
	stmt->execute(insertMomentQueryStdString);


	delete con;
	delete stmt;
}

void caviar_hits::addCaviarHit(Blob *blob)
{

	for (auto &region : blob->getAllRegions()) // access by reference to avoid copying
	{

		caviar_hits hh;
		hh.addCaviarHit(blob->hitId, region.regionId,blob->human_id_actual, region.getAverageMoment(), region.getStandardDeviationMoment(), region.getSkewnessMoment());


		//addHumanHit(blob.id+"_"+region.id,"",blob.id,)
	}



}


void caviar_hits::addCaviarHit(string img_id, string region_id, string human_id_actual, MomentAverage *momentAverage, MomentStandardDeviation *momentStandardDeviation, MomentSkewness *momentSkewness)
{
	
	int intRegionId = 0;
	if (region_id == "Top")
	{
		intRegionId = 1;
	}
	else if (region_id == "Middle")
	{
		intRegionId = 2;
	}
	else
	{
		intRegionId = 3;
	}
	int inthuman_id_actual = stoi(human_id_actual);
	addCaviarHit(
		img_id,
		intRegionId,
		inthuman_id_actual,
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

std::auto_ptr< sql::ResultSet > caviar_hits::getAllProfilesData()
{
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

	stmt = con->createStatement();
	stmt->execute("USE camera");

	string tryGetCurrentImageQuery = "SELECT * FROM caviar_hits";
	std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(tryGetCurrentImageQuery));

	return res;
}

void getRegionFromResult( sql::ResultSet *res, Region *region)
{

	MomentAverage *momentAvg = new MomentAverage(res->getDouble("av0"), res->getDouble("av1"), res->getDouble("av2"));
	MomentStandardDeviation *momentStdDev =  new MomentStandardDeviation(res->getDouble("stdDev0"), res->getDouble("stdDev1"), res->getDouble("stdDev2"));
	MomentSkewness *momentSkew = new MomentSkewness(res->getDouble("skew0"), res->getDouble("skew1"), res->getDouble("skew2"));
	region->setMoments(momentAvg, momentStdDev, momentSkew);
}

double getDistanceBetweenBlobs(Blob *blob1, Blob *blob2)
{
	double total = 0;
	vector<Region>::iterator it = blob1->getAllRegions().begin();
	for (; it != blob1->getAllRegions().end(); ++it)
	{
		Region x = *it;
	}
	return 0;
}

void caviar_hits::compareAllHits()
{


	string tryGetCurrentImageQuery = "SELECT * FROM moments";
	//auto_ptr< sql::ResultSet > res(stmt->executeQuery(tryGetCurrentImageQuery));
	//auto_ptr< sql::ResultSet > resCompared(stmt->executeQuery(tryGetCurrentImageQuery));
	string cached_img_id = "";
	Blob blob1;
	Blob blob2;
	string profileIdRegex;
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
	stmt = con->createStatement();
	stmt->execute("USE camera");

	vector<string> imgIds;

	/*
	string currentProfileQuery1 = "SELECT img_id FROM caviar_hits";
	ResultSet *imgSpecificResult1 = stmt->executeQuery(currentProfileQuery1);
	while (imgSpecificResult1->next())
	{
		imgIds.push_back(imgSpecificResult1->getString(1));
	}
	vector<string> imgIds2(imgIds);
	*/

	/*Insert all combinations of caviar images
	string insertQuery = "INSERT INTO caviar_hits_comparison(testing_image, control_image) VALUES('";
	for (int i = 0; i < imgIds.size(); i++)
	{
	for (int j = i; j < imgIds.size(); j++)
	{
	string finalInsertQuery = insertQuery +  imgIds[i] + "','"+ imgIds2[j]+"')";
	qDebug() << QString::fromStdString(finalInsertQuery);
	stmt->executeUpdate(finalInsertQuery);

	}
	}*/

	/*Insert all combinations of caviar images
	string insertQuery = "INSERT INTO caviar_hits_comparison(testing_image, control_image) VALUES('";
	for (int i = 0; i < imgIds.size(); i++)
	{
	for (int j = i; j < imgIds.size(); j++)
	{
	string finalInsertQuery = insertQuery +  imgIds[i] + "','"+ imgIds2[j]+"')";
	qDebug() << QString::fromStdString(finalInsertQuery);
	stmt->executeUpdate(finalInsertQuery);

	}
	}*/

	string currentProfileQuery1 = "SELECT control_image,testing_image FROM caviar_hits_comparison";
	ResultSet *imgSpecificResult1 = stmt->executeQuery(currentProfileQuery1);
	while (imgSpecificResult1->next())
	{
		string control_img_id = imgSpecificResult1->getString(1);
		string testing_img_id = imgSpecificResult1->getString(2);
		string mom_q = "SELECT * FROM moments where ";
		ResultSet *control_img_moments = stmt->executeQuery(mom_q + "control_image= " + control_img_id);
		ResultSet *testing_img_moments = stmt->executeQuery(mom_q + "testing_image= " + testing_img_id);
	}
}

 