#ifndef MESSAGEPASSER_H
#define MESSAGEPASSER_H

#include <QObject>
#include "Models.h"
#include "threadfornode.h"

using namespace models;

class MessagePasser : public QObject
{
	Q_OBJECT

public:
    MessagePasser(QObject *parent = 0);
    ~MessagePasser();

public slots:
	void passMessage(ProfileTransferObj profile, ThreadForNode* nodeThread);

private:
    
};

#endif // MESSAGEPASSER_H
