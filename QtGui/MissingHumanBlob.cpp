#include "Models.h"
#include <ctime>

using namespace models;

MissingHumanBlob::MissingHumanBlob(){};

MissingHumanBlob::MissingHumanBlob(models::HumanBlob superHumanBlob)
{
	humanBlob = superHumanBlob;
	time(&missedTime);
}

MissingHumanBlob::~MissingHumanBlob(){}