#ifndef CABOUT_H
#define CABOUT_H

#include "command.h"
#include "aboutdialog.h"
class cAbout : public Command
{
public:
    cAbout();
    void exec()const override;
};

#endif // CABOUT_H
