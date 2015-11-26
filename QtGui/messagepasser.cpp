#include "messagepasser.h"

MessagePasser::MessagePasser(QObject *parent)
	: QObject(parent)
{

}

MessagePasser::~MessagePasser()
{

}

void MessagePasser::passMessage(ProfileTransferObj profile, ThreadForNode* nodeThread)
{
	nodeThread->updateProfileList(profile);
}