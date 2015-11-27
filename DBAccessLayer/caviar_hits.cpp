#include "caviar_hits.h"
#include <windows.h> // for Sleep


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

double getDistanceBetweenBlobs(Blob *controlBlob, Blob *testingBlob)
{
	double total = 0;
	vector<Region> controlRegions = controlBlob->getAllRegions();
	vector<Region> testingRegions = testingBlob->getAllRegions();
	double cHueCoef = 0.7, cSatCoef = 0.2,cValCoef = 0.1;
	double rHeadCoef = 0.1, rTorsCoef = 0.5, rLegCoef = 0.4;
	map<int, double> regionMap;
	regionMap[0] = rHeadCoef, regionMap[1] = rTorsCoef, regionMap[2] = rLegCoef;
	double totalDistanceSquared = 0;



	MomentAverage* cRAve; 
	MomentAverage* tRAve;
	MomentStandardDeviation* cRStdDev;
	MomentStandardDeviation* tRStdDev;
	MomentSkewness* cRSkew;
	MomentSkewness* tRSkew;
	for (int rId = 0; rId < 3; rId++)
	{
		cRAve = controlRegions[rId].getAverageMoment(); //c = control , R = Region
		tRAve = testingRegions[rId].getAverageMoment(); //t = testing
		double rAveDistance =	cHueCoef*qPow(cRAve->channel0 - tRAve->channel0,2) +
								cSatCoef*qPow(cRAve->channel1 - tRAve->channel1,2) +
								cValCoef*qPow(cRAve->channel2 - tRAve->channel2,2);

		cRStdDev = controlRegions[rId].getStandardDeviationMoment(); //c = control , R = Region
		tRStdDev = testingRegions[rId].getStandardDeviationMoment(); //t = testing
		double rStandardDev =	cHueCoef*(double)qPow(cRStdDev->channel0 - tRStdDev->channel0, 2) +
								cSatCoef*(double)qPow(cRStdDev->channel1 - tRStdDev->channel1, 2) +
								cValCoef*(double)qPow(cRStdDev->channel2 - tRStdDev->channel2, 2);

		cRSkew = controlRegions[rId].getSkewnessMoment(); //c = control , R = Region
		tRSkew = testingRegions[rId].getSkewnessMoment(); //t = testing
		double rSkewNess =	cHueCoef*(double)qPow(cRSkew->channel0 - tRSkew->channel0, 2) +
							cSatCoef*(double)qPow(cRSkew->channel1 - tRSkew->channel1, 2) +
							cValCoef*(double)qPow(cRSkew->channel2 - tRSkew->channel2, 2);

		totalDistanceSquared += regionMap[rId]*(rAveDistance + rStandardDev + rSkewNess);
	}
	totalDistanceSquared = qSqrt(totalDistanceSquared);
	delete	cRAve;
	delete	tRAve;
	delete	cRStdDev;
	delete	tRStdDev;
	delete	cRSkew;
	delete	tRSkew;
	return totalDistanceSquared;
}

void caviar_hits::compareAllHits()
{


	string tryGetCurrentImageQuery = "SELECT * FROM moments";
	//auto_ptr< sql::ResultSet > res(stmt->executeQuery(tryGetCurrentImageQuery));
	//auto_ptr< sql::ResultSet > resCompared(stmt->executeQuery(tryGetCurrentImageQuery));
	string cached_img_id = "";

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



	string currentProfileQuery1 = "SELECT control_image,testing_image FROM caviar_hits_comparison WHERE distance IS NULL";
	ResultSet *imgSpecificResult1 = stmt->executeQuery(currentProfileQuery1);
	int loopCounter = 0;
	while (imgSpecificResult1->next() && false)//Not used
	{
		string control_img_id = imgSpecificResult1->getString(1);
		string testing_img_id = imgSpecificResult1->getString(2);
		string mom_q = "SELECT * FROM moments where ";
		string check = mom_q + "img_id= '" + control_img_id + "'";
		ResultSet *control_img_moments = stmt->executeQuery(mom_q + "img_id= '" + control_img_id+"'");
		ResultSet *testing_img_moments = stmt->executeQuery(mom_q + "img_id= '" + testing_img_id+"'");

		Blob *blobControl = new Blob();
		Blob *blobTesting = new Blob();
		Region *regionControl;
		Region *regionTesting;
		while (control_img_moments->next() && testing_img_moments->next()) {
			regionControl = new Region();
			regionTesting = new Region();

			getRegionFromResult(control_img_moments, regionControl);
			getRegionFromResult(testing_img_moments, regionTesting);

			regionControl->regionId = control_img_moments->getInt("region_id");
			regionTesting->regionId = testing_img_moments->getInt("region_id");

			blobControl->addRegion(regionControl);
			blobTesting->addRegion(regionTesting);

		}
		double distance = getDistanceBetweenBlobs(blobControl, blobTesting);
		qDebug() << QString::fromStdString("The Distance for " + testing_img_id + " AND " + control_img_id + " is = " + to_string(distance));
		string updateDistance = "UPDATE caviar_hits_comparison SET  distance = " + to_string(distance) + 
								" WHERE control_image='" + control_img_id+ "' AND " +
								"testing_image='" + testing_img_id+"'" ;
		stmt->executeUpdate(updateDistance);
		delete regionControl;
		delete regionTesting;
		delete blobControl;
		delete blobTesting; 
		delete control_img_moments;
		delete testing_img_moments;
	}
	
	delete imgSpecificResult1;

	string evaluateDistance = "SELECT * FROM caviar_hits_comparison";
	imgSpecificResult1 = stmt->executeQuery(currentProfileQuery1);



	

	
}

 