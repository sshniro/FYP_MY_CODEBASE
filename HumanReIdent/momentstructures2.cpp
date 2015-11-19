#include "stdafx.h"
#include "momentstructures2.h"

MomentStructures2::MomentStructures2()
{

}

MomentAverage::MomentAverage(double av0, double av1, double av2)
{

	channel0 = av0;
	channel1 = av1;
	channel2 = av2;

}

MomentAverage::MomentAverage(double av0)
{

	channel0 = av0;
	channel1 = -1;
	channel2 = -1;

}


MomentStandardDeviation::MomentStandardDeviation(double stdDev0, double stdDev1, double stdDev2)
{
	channel0 = stdDev0;
	channel1 = stdDev1;
	channel2 = stdDev2;

}
MomentStandardDeviation::MomentStandardDeviation(double stdDev)
{

	channel0 = stdDev;
	channel1 = -1;
	channel2 = -1;

}
MomentSkewness::MomentSkewness(double av0, double av1, double av2)
{
	channel0 = av0;
	channel1 = av1;
	channel2 = av2;

}
MomentSkewness::MomentSkewness(double av0)
{

	channel0 = av0;
	channel1 = -1;
	channel2 = -1;

}

///////////////Region Implementations//////////////////
Region::Region(std::string regionId, int startRow, int startCol, int endRow, int endCol)
{
	this->regionId = regionId;
	this->startCol = startCol;
	this->endCol = endCol;
	this->startRow = startRow;
	this->endRow = endRow;
}

Region::Region(){

	this->regionId = "";
	this->startRow = 0;
	this->startCol = 0;
	this->endRow = 0;
	this->endCol = 0;


}

Region::~Region(){

}

void Region::setRegionId(std::string regionId){
	this->regionId = regionId;
}

void Region::setMoments(MomentAverage *momentAverage, MomentStandardDeviation *momentStandardDeviation, MomentSkewness *momentSkewness)
{
	this->momentAverage = momentAverage;
	this->momentStandardDeviation = momentStandardDeviation;
	this->momentSkewness = momentSkewness;
}


MomentAverage* Region::getAverageMoment()
{
	return momentAverage;
}

MomentStandardDeviation* Region::getStandardDeviationMoment()
{
	return momentStandardDeviation;
}

MomentSkewness* Region::getSkewnessMoment()
{
	return momentSkewness;
}
////////////////////////////////////////////////////////////////


///////////////////Blob Implementations
Blob::Blob(){
	this->hitId = "";
	this->rows = 0;
	this->cols = 0;
	this->timeStamp = "";
	this->regions.clear();
}

Blob::Blob(std::string id, int rows, int cols, std::string timeStamp) 
{

	this->hitId = id;
	this->rows = rows;
	this->cols = cols;
	this->timeStamp = timeStamp;
}


void Blob::addRegion(Region *region)
{
	//Region xregion = *region;
	this->regions.push_back(*region);
	//this->regions.push_back(xregion);
}

std::vector<Region> Blob::getAllRegions()
{
	return this->regions;
}




MomentAverage::~MomentAverage(){

}

MomentStandardDeviation::~MomentStandardDeviation(){

}

MomentSkewness::~MomentSkewness(){

}

Blob::~Blob(){

}

