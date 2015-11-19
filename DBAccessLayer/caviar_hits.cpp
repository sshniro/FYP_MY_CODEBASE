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
	for (int profileId = 1; profileId < 73; profileId++)
	{
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");

		stmt = con->createStatement();
		stmt->execute("USE camera");

		if (profileId > 9)
		{
			tryGetCurrentImageQuery += "'00" + to_string(profileId) + "%'";
			profileIdRegex = "'00" + to_string(profileId) + "%'";//
		}
		else
		{
			tryGetCurrentImageQuery += "'000" + to_string(profileId) + "%'";
			profileIdRegex = "'000" + to_string(profileId) + "%'";//
		}
		try{
			string tryGetCurrentImageQueryX = "UPDATE moments SET profileId=" + to_string(profileId) + " WHERE img_id LIKE" + profileIdRegex;//
			stmt->executeQuery(tryGetCurrentImageQueryX);
		}


		/*
		for (int hitId = 1;; hitId++)
		{
			string tryGetCurrentImageQuery = "SELECT * FROM moments WHERE img_id LIKE";
			if (profileId > 9)
			{
				tryGetCurrentImageQuery += "'00" + to_string(profileId) + "%'";
			}
			else
			{
				tryGetCurrentImageQuery += "'000" + to_string(profileId) + "%'";
			}

			ResultSet *imgSpecificResult = stmt->executeQuery(tryGetCurrentImageQuery);
			int regionCounter = 0;
			Region *region = new Region();

			if (imgSpecificResult->rowsCount != 0)
			{
				while (imgSpecificResult->next())
				{
					getRegionFromResult(imgSpecificResult, region);
					//region.regionId = to_string(regionCounter);
					region->setRegionId(to_string(regionCounter));
					regionCounter++;
					blob1.addRegion(region);


				}
				for (int j = profileId; j < 73; j++)
				{
					string tryGetCurrentImageQuery = "SELECT * FROM moments WHERE img_id LIKE";
					if (j > 9)
					{
						tryGetCurrentImageQuery += "'00" + to_string(profileId) + "%'";
					}
					else
					{
						tryGetCurrentImageQuery += "'000" + to_string(profileId) + "%'";
					}

					ResultSet *imgSpecificResult(stmt->executeQuery(tryGetCurrentImageQuery));
					int regionCounter = 0;
					Region region;
					while (imgSpecificResult->next()) {
						getRegionFromResult(imgSpecificResult, &region);
						region.regionId = to_string(regionCounter);
						regionCounter++;
						blob2.addRegion(&region);
					}
					getDistanceBetweenBlobs(&blob1, &blob2);
				}
			}
			else
			{
				break;
			}
		}*/


	}
}

 