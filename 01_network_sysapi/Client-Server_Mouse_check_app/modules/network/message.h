#ifndef MESSAGE_H
#define MESSAGE_H

#include "messages.h"

struct Message
{
    MessageType type;
    union{
        MessageMouseActivityStatus mouseActivityStatus;
    } message;
};

#endif // MESSAGE_H
