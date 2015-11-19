#ifndef CAVIAR_HITS_H
#define CAVIAR_HITS_H

#include "stdafx.h"
#include "dbaccesslayer_global.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <QtCore\qdiriterator.h>
#include <QtCore\qstring.h>
#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>

#include <stdio.h>

#include "MomentStructures2.h"
using namespace std;
using namespace sql;
using namespace mysql;

class DBACCESSLAYER_EXPORT caviar_hits
{
public:
	caviar_hits();
	~caviar_hits();
	void addCaviarHit(Blob *blob);
	void addCaviarHit(string img_id, string region_id, string human_id_actual, MomentAverage *momentAverage, MomentStandardDeviation *momentStandardDeviation, MomentSkewness *momentSkewness);
	void addCaviarHit(string img_id, int region_id, int human_id_actual, double av0, double av1, double av2, double stdDev0, double stdDev1, double stdDev2, double skew0, double skew1, double skew2);
	void compareAllHits();
	std::auto_ptr< sql::ResultSet > getAllProfilesData();

private:
	MySQL_Driver *driver;
	Connection *con;
	Statement *stmt;
};

#endif 