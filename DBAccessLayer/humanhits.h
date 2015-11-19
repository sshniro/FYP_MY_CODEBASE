#ifndef HUMANHITS_H
#define HUMANHITS_H

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
using namespace sql;
using namespace mysql;
using namespace std;
class DBACCESSLAYER_EXPORT HumanHits
{
	public:
		HumanHits();
		HumanHits(MySQL_Driver *driver, Connection *con);
		~HumanHits();

		void addHumanHit(string id, string path, string hit_id, double av0, double av1, double av2, double stdDev0, double stdDev1, double stdDev2, double skew0, double skew1, double skew2);
		void addHumanHit(Blob *blob);
		void addHumanHit(string hitId, string regionId, MomentAverage *momentAverage, MomentStandardDeviation *momentStandardDev, MomentSkewness *momentSkeww);



	private:
		MySQL_Driver *driver;
		Connection *con;
		Statement *stmt;


};

#endif // HUMANHITS_H