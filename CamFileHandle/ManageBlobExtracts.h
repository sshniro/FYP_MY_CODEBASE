#ifndef MANAGEBLOBEXTRACTS_H
#define MANAGEBLOBEXTRACTS_H

#include "camfilehandle_global.h"

class CAMFILEHANDLE_EXPORT ManageBlobExtracts
{
public:
	void removeSmallFiles(QString index, QString actual, int maxSize = 5000);


	ManageBlobExtracts();
	~ManageBlobExtracts();

private:

};

#endif 
