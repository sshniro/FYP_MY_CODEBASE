#include "camfilehandle.h"

#include <QtCore\qstring.h>
#include <QtCore\qdiriterator.h>
#include <QtCore\qstring.h>
#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>

class CAMFILEHANDLE_EXPORT ManageBlobExtracts
{
	public:
		/*
		  The File name formats should be _box_, _cmask_, _convex_,_frame_
		*/
		void removeSmallFiles(QString index, QString actual, int maxSize = 5000){


			QDirIterator index_it(index, QDir::Files);


			while (index_it.hasNext())
			{
				qDebug() << "Processing: " << index_it.next();

				bool result;
				QFileInfo fileInfo = index_it.fileInfo();
				int size = fileInfo.size();
				if (size < maxSize)
				{
					QString absoluteFilePath = fileInfo.absoluteFilePath();
					QString box_file_Name = fileInfo.fileName();

					QString cmask_file_Name = fileInfo.fileName();
					cmask_file_Name.replace("_box_", "_cmask_");
					QString convex_file_Name = fileInfo.fileName();
					convex_file_Name.replace("_box_", "_convex_");
					QString frame_file_Name = fileInfo.fileName();
					frame_file_Name.replace("_box_", "_frame_");

					QDir directory(index);
					directory.remove(box_file_Name);
					directory.remove(cmask_file_Name);
					directory.remove(convex_file_Name);
					directory.remove(frame_file_Name);

					if (!actual.trimmed().isEmpty()){
						QDir directoryAct(actual);
						directoryAct.remove(box_file_Name);
						directoryAct.remove(cmask_file_Name);
						directoryAct.remove(convex_file_Name);
						directoryAct.remove(frame_file_Name);
					}

					//qDebug() << file;
					//result = QFile::remove(it.fileInfo().absoluteFilePath());


				}
			}
		}

		ManageBlobExtracts();
		~ManageBlobExtracts();

	private:

};
ManageBlobExtracts::ManageBlobExtracts(){

}

ManageBlobExtracts::~ManageBlobExtracts(){

}