#ifndef CQUIT_H
#define CQUIT_H

#include "command.h"

class cQuit : public Command
{
public:
    void exec()const override;
};

#endif // CQUIT_H
