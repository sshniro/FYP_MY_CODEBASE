#ifndef THREADFORNODE_H
#define THREADFORNODE_H

#include <QObject>
#include "QtCore\qthread.h"
#include "Models.h"

using namespace models;

class ThreadForNode : public QThread
{
	Q_OBJECT

public:
	ThreadForNode();
	~ThreadForNode();
	void run();
	void updateProfileList(ProfileTransferObj profile);

signals:
	void sendProfileToNode(ProfileTransferObj profile, ThreadForNode* nodeThread);

private:
	MessagePasser* msgPasser;
};

#endif // THREADFORNODE_H
