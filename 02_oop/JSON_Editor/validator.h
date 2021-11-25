#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <algorithm>
class Validator
{
private:
    int i;
    QString str;
    bool S();
    bool EXP();
    bool VAR();
    bool VAR1();
    bool VAL();
    bool CH();
    bool NUM();
    bool C();
    bool C0();
    bool K();
    bool STR();
    bool ARR();
public:
    bool exec(QString);
};

#endif // VALIDATOR_H
