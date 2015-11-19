#include "Models.h"

using namespace models;

Blob::Blob(){};

Blob::Blob(vector<Point> _contour)
{
	contour = _contour;
	mu = moments(contour, false);
	mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
}

vector<Point> Blob::getContour()
{
	return contour;
}

void Blob::setContour(vector<Point> _contour)
{
	contour = _contour;
	mu = moments(contour, false);
	mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
}

Moments Blob::getMoments()
{
	return mu;
}

Point2f Blob::getmassCenter()
{
	return mc;
}

Blob::~Blob(){}