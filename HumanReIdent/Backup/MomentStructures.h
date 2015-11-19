#ifndef MOMENTSTRUCTURES_H
#define MOMENTSTRUCTURES_H

#include <QObject>
#include "humanreident_global.h"
#include <stdafx.h>

class HUMANREIDENT_EXPORT MomentStructures
{ 

public:
	int channel0;
	int channel1;
	int channel2;
	MomentStructures();
	~MomentStructures();

	
};


class HUMANREIDENT_EXPORT MomentAverage : public MomentStructures
{
public:

	MomentAverage(double av);
	MomentAverage(double av0, double av1, double av2);

	~MomentAverage();

	
};

class HUMANREIDENT_EXPORT MomentStandardDeviation : public MomentStructures
{
public:
	MomentStandardDeviation(double stdDev);
	MomentStandardDeviation(double stdDev0, double stdDev1, double stdDev2);
	~MomentStandardDeviation();

};

class HUMANREIDENT_EXPORT MomentSkewness : public MomentStructures
{
public:
	MomentSkewness(double skew0);
	MomentSkewness(double skew0, double skew1, double skew2);
	~MomentSkewness();


};

class HUMANREIDENT_EXPORT Region
{
public:
	std::string regionId;
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	Region(std::string id, int startRow, int startCol, int endRow, int endCol);
	void setMoments(MomentAverage momentAverage, MomentStandardDeviation momentStandardDeviation, MomentSkewness momentSkewness);
	MomentAverage getAverageMoment();
	MomentStandardDeviation getStandardDeviationMoment();
	MomentSkewness getSkewnessMoment();
	~Region();

private:
	MomentAverage *momentAverage;
	MomentStandardDeviation *momentStandardDeviation;
	MomentSkewness *momentSkewness;

};


class HUMANREIDENT_EXPORT Blob
{
public:
	std::string hitId;
	std::string path;
	int rows;
	int cols;
	std::string timeStamp;
	Blob(std::string id, int rows, int cols, std::string timeStamp="");
	void addRegion(Region region);
	void removeRegion(std::string id);
	std::vector<Region> getAllRegions();


	~Blob();

private:
	std::vector<Region> regions;

};
#endif // MOMENTSTRUCTURES_H
