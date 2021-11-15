#include "cabout.h"

cAbout::cAbout()
{

}
void cAbout::exec()const{
    aboutDialog about;
    about.exec();
}
