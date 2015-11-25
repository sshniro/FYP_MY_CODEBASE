#include "messagepasser.h"

MessagePasser::MessagePasser(QObject *parent = 0)
	: QObject(parent)
{

}

MessagePasser::~MessagePasser()
{

}


// slots

void passMessage(ProfileTransferObj profile, ThreadForNode* nodeThread)
{
	nodeThread->updateProfileList(profile);
}