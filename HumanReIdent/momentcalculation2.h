#ifndef MOMENTCALCULATION2_H
#define MOMENTCALCULATION2_H
#include <opencv2/core/core.hpp>
#include "MomentStructures2.h"
#include <humanreident_global.h>
using namespace cv;
class HUMANREIDENT_EXPORT MomentCalculation2
{


public:
	MomentCalculation2();
	~MomentCalculation2();
	MomentAverage getAverageColourInConvexRegion(Mat image, Mat imageMask, Region *region);
	MomentStandardDeviation getStandardDeviationInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage);
	MomentSkewness getSkewnessnInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage);

private:
	
};

#endif // MOMENTCALCULATION2_H
