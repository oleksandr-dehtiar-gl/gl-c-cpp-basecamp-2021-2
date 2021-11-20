#include "cquit.h"
#include "QApplication"
void cQuit::exec() const
{
    QApplication::quit();
}
