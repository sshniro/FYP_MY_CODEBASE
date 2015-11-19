#ifndef MOMENTSCALCULATION_H
#define MOMENTSCALCULATION_H
#include <humanreident_global.h>
#include <QObject>
#include <opencv2/core/core.hpp>
#include "MomentStructures2.h"
using namespace cv;
class HUMANREIDENT_EXPORT MomentsCalculation : public QObject
{
	Q_OBJECT

public:

	MomentsCalculation(QObject *parent=0);
	~MomentsCalculation();
	MomentAverage getAverageColourInConvexRegion(Mat image, Mat imageMask, Region region);
	MomentStandardDeviation getStandardDeviationInConvexRegion(Mat image, Mat imageMask, Region region, MomentAverage momentAverage);
	MomentSkewness getSkewnessnInConvexRegion(Mat image, Mat imageMask, Region region, MomentAverage momentAverage);

private:
	
};

#endif // MOMENTS_H
