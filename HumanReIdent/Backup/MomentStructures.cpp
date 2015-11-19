#include "stdafx.h"
#include "MomentStructures.h"

MomentStructures::MomentStructures()
{

}

MomentAverage::MomentAverage(double av0)
{

	channel0 = av0; 
	channel1 = -1;
	channel2 = -1;

}



//////Standard deviation

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

Region::Region(std::string regionId, int startRow, int startCol, int endRow, int endCol)
{
	this->regionId = regionId;
	this->startCol = startCol;
	this->endCol = endCol;
	this->startRow = endRow;
	this->endRow = endRow;
}

void Region::setMoments(MomentAverage momentAverage, MomentStandardDeviation momentStandardDeviation, MomentSkewness momentSkewness)
{
	this->momentAverage  =  &momentAverage;
	this->momentStandardDeviation = &momentStandardDeviation;
	this->momentSkewness = &momentSkewness;
}

Blob::Blob(std::string id, int rows, int cols, std::string timeStamp)
{
	this->hitId = id;
	this->rows = rows;
	this->cols = cols;
	this->timeStamp = timeStamp;
}


void Blob::addRegion(Region region)
{
	this->regions.push_back(region);
}

std::vector<Region> Blob::getAllRegions()
{
	return this->regions;
}